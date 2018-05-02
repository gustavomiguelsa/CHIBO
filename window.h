//==========================================================================================
//Window construction class 
//Created by Gustavo Assunção
//==========================================================================================

#ifndef WINDOW_H
#define WINDOW_H

//-----------------------------------------------------------------------------------------

#include </home/gustavo/Desktop/opengl_prj/glad.h>
#include </home/gustavo/Desktop/opengl_prj/glfw3.h>
#include </home/gustavo/Desktop/opengl_prj/camera.h>

#include <iostream>

//-----------------------------------------------------------------------------------------

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 1.0f));

//-----------------------------------------------------------------------------------------

class Window{

public:

	GLFWwindow* window;

	//---------------------------------------------------------------------------------

	// constructor generates the window
	Window(){

		// glfw: initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X	
		#endif

		// glfw window creation
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CHIBO v1.0 ©2018 - Gustavo Assuncao", NULL, NULL);
		if(window == NULL){
		
			std::cout << "Failed to construct GLFW window" << std::endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

                glfwSetCursorPosCallback(window, mouse_callback);
    		glfwSetScrollCallback(window, scroll_callback);

    		// tell GLFW to capture our mouse
    		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	
		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){

			std::cout << "Failed to initialize GLAD" << std::endl;
       
		}

		glEnable(GL_DEPTH_TEST);
	}

	//---------------------------------------------------------------------------------

	void render(){

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//---------------------------------------------------------------------------------
	
	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	void processInput(){

		float currentFrame = glfwGetTime();
      		  deltaTime = currentFrame - lastFrame;
      		  lastFrame = currentFrame;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        		glfwSetWindowShouldClose(window, true);

    		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        		camera.ProcessKeyboard(FORWARD, deltaTime);
   		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        		camera.ProcessKeyboard(BACKWARD, deltaTime);
    		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        		camera.ProcessKeyboard(LEFT, deltaTime);
    		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        		camera.ProcessKeyboard(RIGHT, deltaTime);
	};

	//---------------------------------------------------------------------------------

	bool windowShouldClose(){

		if(glfwWindowShouldClose(window))
			return true;
		else
			return false;
	};

	//---------------------------------------------------------------------------------

	void swapNPoll(){

		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	//---------------------------------------------------------------------------------
	
	void windowTerminate(){

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
    
	}    

	//---------------------------------------------------------------------------------

	// glfw: whenever the mouse moves, this callback is called
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
	    if (firstMouse)
	    {
	        lastX = xpos;
	        lastY = ypos;
	        firstMouse = false;
	    }
	
	    float xoffset = xpos - lastX;
	    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	
	    lastX = xpos;
	    lastY = ypos;
	
	    camera.ProcessMouseMovement(xoffset, yoffset);
	}
	
	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
	    camera.ProcessMouseScroll(yoffset);
	}


private:
    
	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
		// make sure the viewport matches the new window dimensions; note that width and height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

};

#endif

//==========================================================================================


