# Sweetie Engine - 3D Rendering Engine
## Introduction
__The Sweetie Engine is a 3D rendering engine designed to create stunning scenes and render them as photos or films. 
This project is the primary focus of my work at the moment, and it is something that I am very passionate about. 
The engine includes all the necessary elements for native rendering, such as buffers, arrays, and shaders, making it efficient and easy to use.__

## Features
### -Fully functioning event system for seamless interaction and communication between different components of the engine
### -Native rendering elements such as buffers, arrays, and shaders
### -Shader parsing functionality for complex shader code interpretation
### -Fully functional camera system for navigating through scenes and viewing them from different angles and perspectives
### -Support for rendering in OpenGL
### -Easy integration with new rendering APIs without requiring alterations to the client application

#Installation
## To install the Sweetie Engine, you will need to clone the repository from GitHub:
### Step 1, Run those commands on your empty folder:
git init

git remote add origin https://github.com/Awakennn21/Sweetie-Engine.git

git pull origin

git fetch

git submodule init

git submodule update

### Setp 2, Run GenerateProjets.bat file inlcuded in this repository.
### Step 3, Open .sln file and Compile and run the project with Ctrl+F5

# Usage
To get started, you'll need to create a file that includes the __#include "Sweetie.h"__ file in your Sandbox project. 
Then, create a class that derives from Sweetie::Application.
This class will serve as the backbone of your project, providing the framework and structure you need to create amazing scenes.

Once you have your application class set up, you'll need to create a method outside of that class with the signature
__Sweetie::Application* Sweetie::CreateApplication();__
This method should return an instance of the class you created earlier. With these steps complete, you're ready to start building your scene!

One of the key features of the Sweetie engine is its dedicated layer system, which is specifically designed for rendering and input handling. 
This layer system makes it easy to create complex, layered scenes that are rich in detail and texture.

But don't just take our word for it - check out this example code provided in 
## [Examples](./SandBox/Examples/) for you to get started with Sweetie Engine


# Conclusion
The Sweetie Engine is a complex and sophisticated piece of software, but it is also intuitive and user-friendly, making it accessible to a wide range of users. 
I am excited to see what new and exciting projects it will be used for in the future. 
