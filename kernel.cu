#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#define N 100

__global__ void kernel(int *a, int *b, int *c)
{
	int globalID = threadIdx.x + blockIdx.x * blockDim.x;
	printf("globalID = %d\n", globalID);
	if (globalID < N)
		c[globalID] = a[globalID] + b[globalID];

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