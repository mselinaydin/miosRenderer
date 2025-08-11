An implementation of Ray Tracing in One Weekend, as decribed here: https://raytracing.github.io/books/RayTracingInOneWeekend.html

Now includes denoising with AI using Intel Open Image Denoise.

To run the project:
Go to root directory of the project in terminal and do these

- mkdir build
- cd build
- cmake ..
- make
- ./miosRenderer

To run oidn denoiser:

- ./miosRenderer -d

Output will show up as "outputImage.ppm" in build folder.

Denoising output will show up as "denoisedOutputImage.ppm" in build folder.

Output image before denoising:
<img width="1200" height="675" alt="outputImage" src="https://github.com/user-attachments/assets/ee992e28-5360-42fe-a0ec-b8075f6a15eb" />

Output image after denoising:
<img width="1200" height="675" alt="denoisedOutputImage" src="https://github.com/user-attachments/assets/bff5ba6b-bda7-45ce-834a-d717d8ef5fd8" />



