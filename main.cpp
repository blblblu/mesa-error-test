#include <iostream>

#include <GLFW/glfw3.h>
#include <globjects/globjects.h>
#include <globjects/Texture.h>
#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>

namespace {
	void errorCallback(int errnum, const char *errmsg) {
		std::cerr << errnum << ": " << errmsg << std::endl;
	}
}

int main(int argc, char **argv) {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  const glm::ivec2 renderSize = {1280, 720};

	GLFWwindow* window = glfwCreateWindow(renderSize.x, renderSize.y, "OpenGL", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	globjects::init();

	globjects::ref_ptr<globjects::Framebuffer> framebuffer = new globjects::Framebuffer();
	globjects::ref_ptr<globjects::Texture> colorTexture = new globjects::Texture(gl::GL_TEXTURE_2D);
	globjects::ref_ptr<globjects::Texture> depthTexture = new globjects::Texture(gl::GL_TEXTURE_2D);

	colorTexture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
	colorTexture->setParameter(gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);
	colorTexture->setParameter(gl::GL_TEXTURE_WRAP_S, gl::GL_CLAMP_TO_EDGE);
	colorTexture->setParameter(gl::GL_TEXTURE_WRAP_T, gl::GL_CLAMP_TO_EDGE);

	depthTexture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
	depthTexture->setParameter(gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);
	depthTexture->setParameter(gl::GL_TEXTURE_WRAP_S, gl::GL_CLAMP_TO_EDGE);
	depthTexture->setParameter(gl::GL_TEXTURE_WRAP_T, gl::GL_CLAMP_TO_EDGE);

	colorTexture->image2D(0, gl::GL_RGBA8, renderSize, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, nullptr);
	colorTexture->clearImage(0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, glm::ivec4(0, 0, 0, 0));

	depthTexture->image2D(0, gl::GL_DEPTH_COMPONENT32F, renderSize, 0, gl::GL_DEPTH_COMPONENT, gl::GL_FLOAT, nullptr);
	depthTexture->clearImage(0, gl::GL_DEPTH_COMPONENT, gl::GL_FLOAT, glm::ivec4(0, 0, 0, 0));

	framebuffer->attachTexture(gl::GL_COLOR_ATTACHMENT0, colorTexture);
	framebuffer->attachTexture(gl::GL_DEPTH_ATTACHMENT, depthTexture);
	framebuffer->setDrawBuffers({gl::GL_COLOR_ATTACHMENT0 /*, gl::GL_DEPTH_ATTACHMENT*/});
	framebuffer->printStatus(true);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		gl::glClearColor(1.f, 0.f, 1.f, 1.f);
		gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}
