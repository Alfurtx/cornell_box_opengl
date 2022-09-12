#include "common.hpp"
#include "camera.cpp"
#include "renderer.cpp"

// TODO(fonsi): Omnidirectional shadow mapping

#include "vertex_data.cpp"

Camera camera;
static double delta_time = 0.0;
double last_frame = 0.0;

internal void process_input(GLFWwindow* window);
internal uint32 load_shaders(void);
internal void cursor_position_callback(GLFWwindow* handle, double x, double y);
internal void load_models(uint32* res);
internal void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
internal void render_quad();

// NOTE(fonsi): FINAL SCENE VERTICES BUFFER TO LOAD INTO OPENGL
std::vector<std::vector<float>> scene_vertices;
uint32 vaos[8];

// SHADER FLAGS
bool gamma = true;

int
main(void)
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);
    
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Cornell Box OpenGL", 0, 0);
    
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);
    
    // TODO(fonsi): setup callbacks
    
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        assert(0, (char *)"Failed to load GLAD");
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_CULL_FACE);
    
    // glfwSwapInterval(1);
    
    //~ SHADERS
    Shader camera_shader, light_shader, debug_depth_quad_shader;
    camera_shader.compile_program((char*)"w:\\cornell_box_opengl\\shaders\\camera.vert",
                                  (char*)"w:\\cornell_box_opengl\\shaders\\camera.frag",
                                  0);
    // light_shader.compile_program((char*)"w:\\cornell_box_opengl\\shaders\\light.vert",
    //                              (char*)"w:\\cornell_box_opengl\\shaders\\light.frag",
    //                              (char*)"w:\\cornell_box_opengl\\shaders\\light.geo");

    light_shader.compile_program((char*)"w:\\cornell_box_opengl\\shaders\\light.vert",
                                 (char*)"w:\\cornell_box_opengl\\shaders\\light.frag",
                                 0);
    debug_depth_quad_shader.compile_program(
                                 (char*)"w:\\cornell_box_opengl\\shaders\\debug_depth_quad.vert",
                                 (char*)"w:\\cornell_box_opengl\\shaders\\debug_depth_quad.frag",
                                 0);
    
    //~ VERTEX loading
    for(uint i = 0; i < 8; i++) {
        std::vector<float> v;
        scene_vertices.push_back(v);
    }
    
    load_models(vaos);

    glm::vec3 light_position(278.0, 548.8, 279.6);
    glm::vec3 light_looking_at(278.0, 0.0, 279.6);
    glm::vec3 light_up(0.0, 0.0, -1.0);

    uint32 depth_map_fbo;
    glGenFramebuffers(1, &depth_map_fbo);

    uint32 depth_map;
    glGenTextures(1, &depth_map);
    glBindTexture(GL_TEXTURE_2D, depth_map);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1920, 1920, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);  
    float border_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color); 
    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    while(!glfwWindowShouldClose(window)) {
        double current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        
        glClearColor(0.2, 0.5, 0.7, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        process_input(window);

        //~ Scene rendering
        // depth map render
        glViewport(0, 0, 1920, 1920);
        glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 light_projection = glm::perspective(glm::radians(90.0f), 2440.0f / 2440.0f, 40.0f, 2000.f);
        glm::mat4 light_view = glm::lookAt(light_position, light_looking_at, light_up);
        light_shader.use();
        light_shader.set_uniform((char*)"view", light_view);
        light_shader.set_uniform((char*)"projection", light_projection);
        glCullFace(GL_FRONT);
        for(int i = 0; i < scene_vertices.size(); i++) {
            if(i != 1 && i != 2) {
                glBindVertexArray(vaos[i]);
                glDrawArrays(GL_TRIANGLES, 0, scene_vertices[i].size());
            }
        }
        glCullFace(GL_BACK);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // normal render
        glViewport(0, 0, 2440, 1440);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera_shader.use();
        camera_shader.set_uniform((char*)"view", camera.get_view());
        camera_shader.set_uniform((char*)"projection", camera.get_projection());
        camera_shader.set_uniform((char*)"light_position", light_position);
        camera_shader.set_uniform((char*)"view_position", camera.position);
        camera_shader.set_uniform((char*)"near_plane", 1.0f);
        camera_shader.set_uniform((char*)"far_plane", 2000.0f);
        camera_shader.set_uniform((char*)"depth_map", 0);
        camera_shader.set_uniform((char*)"light_view", light_view);
        camera_shader.set_uniform((char*)"light_projection", light_projection);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depth_map);
        for(int i = 0; i < scene_vertices.size(); i++) {
            camera_shader.set_uniform((char*)"is_lamp", i == 1);
            camera_shader.set_uniform((char*)"is_ceiling", i == 2);
            glBindVertexArray(vaos[i]);
            glDrawArrays(GL_TRIANGLES, 0, scene_vertices[i].size());
        }

        // debug_depth_quad_shader.use();
        // debug_depth_quad_shader.set_uniform("near_plane", 1.0f);
        // debug_depth_quad_shader.set_uniform("far_plane", 2000.0f);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, depth_map);
        // render_quad();

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glfwTerminate();
    return(0);
}

internal void 
process_input(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.process_keyboard(Direction::FORWARD, delta_time);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.process_keyboard(Direction::BACKWARD, delta_time);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.process_keyboard(Direction::LEFT, delta_time);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.process_keyboard(Direction::RIGHT, delta_time);
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.process_keyboard(Direction::DOWN, delta_time);
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.process_keyboard(Direction::UP, delta_time);
}

internal void
cursor_position_callback(GLFWwindow* handle, double x, double y)
{
    if(camera.firstmouse) {
        camera.lastx = (float)x;
        camera.lasty = (float)y;
        camera.firstmouse = false;
    }
    float xoff = (float) x - camera.lastx;
    float yoff = (float) y - camera.lasty;
    camera.lastx = (float) x;
    camera.lasty = (float) y;
    camera.process_cursor(xoff, yoff);
}

internal void
load_models(uint* res)
{
    assert(res, (char*)"VAO array passed is null, needs to be an array");
    
    for(uint32 i = 0; i < model_list.size(); i++) {
        
        // calculate normal vecs
        std::vector<glm::vec3> vector_positions;
        for(uint m = 0; m < model_list[i].size() / 6; m++) {
            glm::vec3 vec(model_list[i][6 * m + 0],
                          model_list[i][6 * m + 1],
                          model_list[i][6 * m + 2]);
            vector_positions.push_back(vec);
        }
        
        glm::vec3 normal = glm::normalize(glm::cross((vector_positions[0] - vector_positions[1]), vector_positions[0] - vector_positions[2]));
        
        for(uint32 j = 0; j < indices_list[i].size(); j++) {
            uint pos = indices_list[i][j];
            
            for(uint k = 0; k < 3; k++) {
                scene_vertices[i].push_back(model_list[i][6 * pos + k]);
            }
            
            for(uint k = 0; k < 3; k++) {
                scene_vertices[i].push_back(model_list[i][6 * pos + k + 3]);
            }
            
            for(uint k = 0; k < 3; k++) {
                scene_vertices[i].push_back(normal[k]); 
            }
        }
        
        uint32 vbo;
        glGenVertexArrays(1, &res[i]);
        glBindVertexArray(res[i]);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * scene_vertices[i].size(), scene_vertices[i].data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
    }
}

internal void 
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_B && action == GLFW_PRESS)
        gamma = !gamma;
}

uint32 quadVAO = 0;
uint32 quadVBO;
internal void 
render_quad()
{
    if (quadVAO == 0) {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}





