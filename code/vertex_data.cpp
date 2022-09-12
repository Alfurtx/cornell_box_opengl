#include "common.hpp"

float flooring[] = {
    552.8, 0.0,   0.0, 1.0, 1.0, 1.0,
    0.0,   0.0,   0.0, 1.0, 1.0, 1.0,
    0.0,   0.0, 559.2, 1.0, 1.0, 1.0,
    549.6, 0.0, 559.2, 1.0, 1.0, 1.0,
};
uint flooring_index[] = {0,1,3,1,2,3};

float light[] = {
    343.0, 548.7, 227.0, 1.0, 1.0, 1.0,
    343.0, 548.7, 332.0, 1.0, 1.0, 1.0,
    213.0, 548.7, 332.0, 1.0, 1.0, 1.0,
    213.0, 548.7, 227.0, 1.0, 1.0, 1.0,
};
uint light_index[] = {0,1,3,1,2,3};

float ceiling[] = {
    556.0, 548.8,   0.0, 1.0, 1.0, 1.0,
    556.0, 548.8, 559.2, 1.0, 1.0, 1.0,
    0.0,   548.8, 559.2, 1.0, 1.0, 1.0,
    0.0,   548.8,   0.0, 1.0, 1.0, 1.0,
};
uint ceiling_index[] = {0,1,3,1,2,3};

float backwall[] = {
    549.6,   0.0, 559.2, 1.0, 1.0, 1.0,
    0.0,   0.0, 559.2, 1.0, 1.0, 1.0,
    0.0, 548.8, 559.2, 1.0, 1.0, 1.0,
    556.0, 548.8, 559.2, 1.0, 1.0, 1.0,
};
uint backwall_index[] = {0,1,3,1,2,3};

float rightwall[] = {
    0.0,   0.0, 559.2, 0.0, 1.0, 0.0,
    0.0,   0.0,   0.0, 0.0, 1.0, 0.0,
    0.0, 548.8,   0.0, 0.0, 1.0, 0.0,
    0.0, 548.8, 559.2, 0.0, 1.0, 0.0,
};
uint rightwall_index[] = {0,1,3,1,2,3};

float leftwall[] = {
    552.8,   0.0,   0.0, 1.0, 0.0, 0.0,
    549.6,   0.0, 559.2, 1.0, 0.0, 0.0,
    556.0, 548.8, 559.2, 1.0, 0.0, 0.0,
    556.0, 548.8,   0.0, 1.0, 0.0, 0.0,
};
uint leftwall_index[] = {0,1,3,1,2,3};

float shortblock[] = {
    130.0, 165.0,  65.0, 0.0, 0.0, 1.0,
    82.0,  165.0, 225.0, 0.0, 0.0, 1.0,
    240.0, 165.0, 272.0, 0.0, 0.0, 1.0,
    290.0, 165.0, 114.0, 0.0, 0.0, 1.0,
    
    290.0,   0.0, 114.0, 0.0, 0.0, 1.0,
    290.0, 165.0, 114.0, 0.0, 0.0, 1.0,
    240.0, 165.0, 272.0, 0.0, 0.0, 1.0,
    240.0,   0.0, 272.0, 0.0, 0.0, 1.0,
    
    130.0,   0.0,  65.0, 0.0, 0.0, 1.0,
    130.0, 165.0,  65.0, 0.0, 0.0, 1.0,
    290.0, 165.0, 114.0, 0.0, 0.0, 1.0,
    290.0,   0.0, 114.0, 0.0, 0.0, 1.0,
    
    82.0,    0.0, 225.0, 0.0, 0.0, 1.0,
    82.0,  165.0, 225.0, 0.0, 0.0, 1.0,
    130.0, 165.0,  65.0, 0.0, 0.0, 1.0,
    130.0,   0.0,  65.0, 0.0, 0.0, 1.0,
    
    240.0,   0.0, 272.0, 0.0, 0.0, 1.0,
    240.0, 165.0, 272.0, 0.0, 0.0, 1.0,
    82.0,  165.0, 225.0, 0.0, 0.0, 1.0,
    82.0,    0.0, 225.0, 0.0, 0.0, 1.0,
};
uint shortblock_index[] = {
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    8, 9, 10, 8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
};

float tallblock[] = {
    423.0, 330.0, 247.0, 0.0, 0.0, 1.0,
    265.0, 330.0, 296.0, 0.0, 0.0, 1.0,
    314.0, 330.0, 456.0, 0.0, 0.0, 1.0,
    472.0, 330.0, 406.0, 0.0, 0.0, 1.0,
    
    423.0,   0.0, 247.0, 0.0, 0.0, 1.0,
    423.0, 330.0, 247.0, 0.0, 0.0, 1.0,
    472.0, 330.0, 406.0, 0.0, 0.0, 1.0,
    472.0,   0.0, 406.0, 0.0, 0.0, 1.0,
    
    472.0,   0.0, 406.0, 0.0, 0.0, 1.0,
    472.0, 330.0, 406.0, 0.0, 0.0, 1.0,
    314.0, 330.0, 456.0, 0.0, 0.0, 1.0,
    314.0,   0.0, 456.0, 0.0, 0.0, 1.0,
    
    314.0,   0.0, 456.0, 0.0, 0.0, 1.0,
    314.0, 330.0, 456.0, 0.0, 0.0, 1.0,
    265.0, 330.0, 296.0, 0.0, 0.0, 1.0,
    265.0,   0.0, 296.0, 0.0, 0.0, 1.0,
    
    265.0,   0.0, 296.0, 0.0, 0.0, 1.0,
    265.0, 330.0, 296.0, 0.0, 0.0, 1.0,
    423.0, 330.0, 247.0, 0.0, 0.0, 1.0,
    423.0,   0.0, 247.0, 0.0, 0.0, 1.0,
};
uint tallblock_index[] = {
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    8, 9, 10, 8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
};

std::vector<float> floor_model(flooring, flooring + sizeof(flooring) / sizeof(float));
std::vector<float> light_model(light, light + sizeof(light) / sizeof(float));
std::vector<float> ceiling_model(ceiling, ceiling + sizeof(ceiling) / sizeof(float));
std::vector<float> backwall_model(backwall, backwall + sizeof(backwall) / sizeof(float));
std::vector<float> leftwall_model(leftwall, leftwall + sizeof(leftwall) / sizeof(float));
std::vector<float> rightwall_model(rightwall, rightwall + sizeof(rightwall) / sizeof(float));
std::vector<float> shortblock_model(shortblock, shortblock + sizeof(shortblock) / sizeof(float));
std::vector<float> tallblock_model(tallblock, tallblock + sizeof(tallblock) / sizeof(float));

std::vector<std::vector<float>> model_list{floor_model, light_model, ceiling_model, backwall_model, leftwall_model, rightwall_model, shortblock_model, tallblock_model};

std::vector<uint> floor_indices(flooring_index, flooring_index + sizeof(flooring_index) / sizeof(uint));
std::vector<uint> light_indices(light_index, light_index + sizeof(light_index) / sizeof(uint));
std::vector<uint> ceiling_indices(ceiling_index, ceiling_index + sizeof(ceiling_index) / sizeof(uint));
std::vector<uint> backwall_indices(backwall_index, backwall_index + sizeof(backwall_index) / sizeof(uint));
std::vector<uint> rightwall_indices(rightwall_index, rightwall_index + sizeof(rightwall_index) / sizeof(uint));
std::vector<uint> leftwall_indices(leftwall_index, leftwall_index + sizeof(leftwall_index) / sizeof(uint));
std::vector<uint> shortblock_indices(shortblock_index, shortblock_index + sizeof(shortblock_index) / sizeof(uint));
std::vector<uint> tallblock_indices(tallblock_index, tallblock_index + sizeof(tallblock_index) / sizeof(uint));

std::vector<std::vector<uint>> indices_list{floor_indices, light_indices, ceiling_indices, backwall_indices, leftwall_indices, rightwall_indices, shortblock_indices, tallblock_indices};
