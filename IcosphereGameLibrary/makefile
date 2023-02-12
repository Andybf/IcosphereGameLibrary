#
# ApoloGameLibrary - makefile for Emscripten
# Created by: Anderson Bucchianico
# Date: feb/2023
#

MAKEFLAGS += --silent

library_src_path = ~/Desktop/IcosphereGameLibrary/IcosphereGameLibrary/source
library_include_path = /Users/anderson/Desktop/IcosphereGameLibrary/IcosphereGameLibrary/include
library_dependency_path = /opt/homebrew/Cellar/sdl2/2.26.2/include

game_lib_name = libIcosphereGameLibrary.a
result_directory = ./lib

all:

	echo "Building..."
	emcc -c\
			$(library_src_path)/Core/Window.cpp\
			$(library_src_path)/Core/Render.cpp\
			$(library_src_path)/Core/Shader.cpp\
			$(library_src_path)/Core/VAO.cpp\
			$(library_src_path)/Core/VBO.cpp\
			$(library_src_path)/Core/EBO.cpp\
			$(library_src_path)/Tools/ModelCreator.cpp\
			$(library_src_path)/World/Entity.cpp\
			$(library_src_path)/World/Camera.cpp\
			$(library_src_path)/World/Projection.cpp\
			$(library_src_path)/World/Cameras/DebugCamera.cpp\
			$(library_src_path)/World/Entities/Light.cpp\
			$(library_src_path)/World/Entities/Text.cpp\
			$(library_src_path)/Inputs/Inputs.cpp\
			$(library_src_path)/Loaders/FileLoader.cpp\
			$(library_src_path)/Loaders/TextureLoader.cpp\
			$(library_src_path)/Loaders/ModelLoader.cpp\
			$(library_src_path)/Loaders/ShaderLoader.cpp\
			$(library_src_path)/Loaders/ModelReaders/StanfordObject.cpp\
			$(library_src_path)/Loaders/ModelReaders/WavefrontObject.cpp\
		-I$(library_include_path)\
		-I$(library_dependency_path)\
		-D AP_DEBUG=1;
	
	emar r $(game_lib_name)\
		Window.o\
		Render.o\
		Shader.o\
		VAO.o\
		VBO.o\
		EBO.o\
		ModelCreator.o\
		Entity.o\
		Camera.o\
		Projection.o\
		DebugCamera.o\
		Light.o\
		Text.o\
		Inputs.o\
		FileLoader.o\
		TextureLoader.o\
		ModelLoader.o\
		ShaderLoader.o\
		StanfordObject.o\
		WavefrontObject.o;
		
	rm \
		Window.o\
		Render.o\
		Shader.o\
		VAO.o\
		VBO.o\
		EBO.o\
		ModelCreator.o\
		Entity.o\
		Camera.o\
		Projection.o\
		DebugCamera.o\
		Light.o\
		Text.o\
		Inputs.o\
		FileLoader.o\
		TextureLoader.o\
		ModelLoader.o\
		ShaderLoader.o\
		StanfordObject.o\
		WavefrontObject.o;
		
	if test -d $(result_directory); then rm -r $(result_directory); fi;
	mkdir $(result_directory);
	mv $(game_lib_name) $(result_directory)
		
	echo "Done."
