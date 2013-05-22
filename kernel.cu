#include <stdio.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include "kernel.cuh"


#define N 100
#define MAX_ITER 500

__device__ float min_d(float a, float b)
{
	return (a<b? a : b);
}

__global__ void kernel(int *a, int *b, int *c)
{
	int globalID = threadIdx.x + blockIdx.x * blockDim.x;
	printf("globalID = %d\n", globalID);
	if (globalID < N)
		c[globalID] = a[globalID] + b[globalID];

}

__global__ void Mandelbrot_kernel(uchar4* ptr, int width, int height, float* palette_d)
{
    // map from threadIdx/BlockIdx to pixel position
    float x = threadIdx.x + blockIdx.x * blockDim.x;
    float y = threadIdx.y + blockIdx.y * blockDim.y;
    int offset = x + y * blockDim.x * gridDim.x;
    
	  float cx = 3.0f * (x / width-0.5f);
	  float cy = 2.0f * (y / height-0.5f);

	//  int i;
 //   float zx = cx;
 //   float zy = cy;
	//	float dx = 0.0f;
	//	float dy = 0.0f; 
 //   //cx *=  cos(time/1000.0f);
 //   //cy *=  sin(time/1000.0f);
	////cx *= 1.0;
	////cy = 0.0;

	//  for(i=0; i<MAX_ITER; i++) {
	//		dx = (zx * zx - zy * zy) + cx + dx;
	//		dy = (zy * zx + zx * zy) + cy + dy;
	//		if((dx * dx + dy * dy) > 4.0f) break;
	//		zx = dx;
	//		zy = dy;
	//  }

			x = 0;
			y = 0;
			int iterNum = 0;
			float xtemp;

			while ( x*x + y*y < 4  &  iterNum < MAX_ITER)
			{
				xtemp = x*x - y*y + cx;
				y = 2*x*y + cy;
				x = xtemp;
				iterNum ++;
			}


	  //unsigned char val = 255.0f*float(i)/MAX_ITER;
	int val = 255.0f*(float)iterNum/MAX_ITER;
	  //printf("offset = %d, i = %d val = %d\n", offset, i, val);

    //
    //ptr[offset].x = min_d(255,3*val/2);
    //ptr[offset].y = (val>300 ? min_d(255,3*(val-100)) : 0);
    //ptr[offset].z = (val>500 ? min_d(255,2*(val-127)) : 0);
//ptr[offset].x = val;
//ptr[offset].y = MAX_ITER - val;
//ptr[offset].z = val*val%255;

ptr[offset].x = palette_d[val]*255;
ptr[offset].y = palette_d[val + 255]*255;
ptr[offset].z = palette_d[val + 510]*255;

//ptr[offset].x = val;
//ptr[offset].y = 255 - val;
//ptr[offset].z = palette_d[val];

    ptr[offset].w = 255;

	//if (offset < 1000)
	//	printf("offset = %d, i = %d val = %d palette.x = %f ptr.x = %f\n", offset, i, val, palette_d[val], ptr[offset].x);

}

extern "C" void launch_kernel()
{
	printf("RUN CUDA KERNEL\n");


	int a[N], b[N], c[N];
	int *dev_a, *dev_b, *dev_c;
	cudaMalloc((void **) &dev_a, N*sizeof(int));
	cudaMalloc((void **) &dev_b, N*sizeof(int));
	cudaMalloc((void **) &dev_c, N*sizeof(int));
	// Fill Arrays
	for (int i = 0; i < N; i++)
	{
		a[i] = i,
			b[i] = 1;
	}
	cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, N*sizeof(int), cudaMemcpyHostToDevice);
	kernel<<<N,1>>>(dev_a, dev_b, dev_c);
	cudaMemcpy(c, dev_c, N*sizeof(int), cudaMemcpyDeviceToHost);
	for (int i = 0; i < N; i++)
	{
		printf("%d + %d = %d\n", a[i], b[i], c[i]);
	}

}

extern "C" void launch_Mandelbrot_kernel(uchar4* ptr, int width, int height)
{
	dim3    blocks(width/16, height/16);
	dim3    threads(16,16);

	// set palette
	float* palette;
	palette = (float*)malloc(255*3*sizeof(float));

for(int i=0; i < 64; i++){
	palette[i + 0] = (4*i)/(float)255;
	palette[i + 255] = (128-2*i)/(float)255;
	palette[i + 510] = (255-4*i)/(float)255;
}
for(int i=0; i < 64; i++){
	palette[64+i + 0] = (float)1;
	palette[64+i + 255] = (4*i)/(float)255;
	palette[64+i + 510] = (float)0;
}
for(int i=0; i < 64; i++){
	palette[128+i + 0] = (128-2*i)/(float)255;
	palette[128+i + 255] = (float)1;
	palette[128+i + 510] = (4*i)/(float)255;
}
for(int i=0; i < 64; i++){
	palette[192+i + 0] = (float)0;
	palette[192+i + 255] = (255-4*i)/(float)255;
	palette[192+i + 510] = (4*i)/(float)255;
}

	float* palette_d;
	cudaMalloc((void **) &palette_d, 255*3*sizeof(float));	
	cudaMemcpy(palette_d, palette, 255*3*sizeof(float), cudaMemcpyHostToDevice);

	Mandelbrot_kernel<<<blocks, threads>>>(ptr, width, height, palette_d);
}