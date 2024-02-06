# Use an official base image with your desired version of GCC or other C++ compiler
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the local source files to the container's working directory
COPY . .

# Compile your C++ code (replace "your_executable_name" with your actual executable name)
RUN g++ -o Tourney_simulator Source.cpp

# Specify the command to run when the container starts (replace "your_executable_name" with your actual executable name)
CMD [ Tourney_simulator]