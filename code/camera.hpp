#if !defined(CAMERA_CPP)
#define CAMERA_CPP

#include "common.hpp"

#define CAMERA_RENDER_DISTANCE 20.0f
#define CAMERA_YAW 90.0f
#define CAMERA_PITCH 0.0f
#define CAMERA_SPEED 300.0f
#define CAMERA_SENSITIVITY 0.1f
#define CAMERA_FOV 45.0f

struct Camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    
    float yaw;
    float pitch;
    double speed;
    float sensitivity;
    float lastx;
    float lasty;
    
    bool firstmouse;
    
    Camera();
    glm::mat4 get_view();
    glm::mat4 get_projection();
    void process_keyboard(Direction direction, double delta_time);
    void process_cursor(float x_offset, float y_offset);
};

#endif
