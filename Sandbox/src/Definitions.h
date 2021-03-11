#pragma once

#define ATLAS_SIZE 8

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 64

#define VIEW_DISTANCE 10

#define RAYCAST_PRECISION 0.1f
#define INTERACT_RANGE 16

const static float TEX_SIZE = 1.f / (float)ATLAS_SIZE;

static const glm::i16vec3 VERTICES[8] = {
	glm::i16vec3(0, 0, 0),
	glm::i16vec3(1, 0, 0),
	glm::i16vec3(1, 1, 0),
	glm::i16vec3(0, 1, 0),
	glm::i16vec3(0, 0, 1),
	glm::i16vec3(1, 0, 1),
	glm::i16vec3(1, 1, 1),
	glm::i16vec3(0, 1, 1),
};

static const uint8_t REV_FACES_INDEX[6] = {1, 0, 3, 2, 5, 4};

static const glm::i16vec3 FACES[6] = {
	glm::i16vec3( 0,  0, -1),		// Back
	glm::i16vec3( 0,  0,  1),		// Front
	glm::i16vec3( 0,  1,  0),		// Top
	glm::i16vec3( 0, -1,  0),		// Bottom
	glm::i16vec3(-1,  0,  0),		// Left
	glm::i16vec3( 1,  0,  0),		// Right
};

//                                       Back          Front         Top           Bottom        Left          Right
static const uint8_t TRIANGLES[6][4] = {{0, 3, 1, 2}, {5, 6, 4, 7}, {3, 7, 2, 6}, {1, 5, 0, 4}, {4, 7, 0, 3}, {1, 2, 5, 6}};

static const glm::vec2 UVS[4] = {
	glm::vec2(0, 0),
	glm::vec2(0, 1),
	glm::vec2(1, 0),
	glm::vec2(1, 1),
};
