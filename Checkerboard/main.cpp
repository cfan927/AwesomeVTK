#include <iostream>

// vtk
#include <vtkSmartPointer.h>
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>
#include <vtkCellData.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

/**
 * params
 * rlt: x,y方向上的方格数量
 * sqrLen: 方格的边长
 */
void CreateCheckerboard(vtkPolyData *grid, int rlt, int sqrLen);

void main()
{
	vtkSmartPointer<vtkPolyData> cb = vtkSmartPointer<vtkPolyData>::New();
	CreateCheckerboard(cb, 10, 5);

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(cb);

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->ResetCamera();

	vtkSmartPointer<vtkRenderWindow> rw = vtkSmartPointer<vtkRenderWindow>::New();
	rw->AddRenderer(renderer);
	rw->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> rwInter = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	rwInter->SetRenderWindow(rw);
	rwInter->Start();
}

void CreateCheckerboard(vtkPolyData *grid, int rlt, int sqrLen)
{
	std::cout << "Create Checkerboard." << std::endl;

	vtkSmartPointer<vtkPlaneSource> planeSource = vtkSmartPointer<vtkPlaneSource>::New();
	planeSource->SetCenter(0.0, 0.0, 0.0);
	planeSource->SetOrigin(0, 0, 0);
	planeSource->SetPoint1(rlt*sqrLen, 0, 0);
	planeSource->SetPoint2(0, rlt*sqrLen, 0);
	planeSource->SetResolution(rlt, rlt);
	planeSource->Update();

	grid->DeepCopy(planeSource->GetOutput());

	vtkSmartPointer<vtkUnsignedCharArray> cellColor = vtkSmartPointer<vtkUnsignedCharArray>::New();
	cellColor->SetNumberOfComponents(3);

	unsigned char cBlack[3] = { 0, 0, 0 };
	unsigned char cWhite[3] = { 255, 255, 255 };
	unsigned char *currentColor = cWhite;
	for (uint32_t i = 0; i < grid->GetNumberOfCells(); i++)
	{
		if (i < rlt || i > rlt * (rlt - 1) || i % rlt == (rlt - 1) || i % rlt == 0) // 周边绘制白色
		{
			currentColor = cWhite;
		}
		else
		{
			// 交错绘制黑白方格
			if ((int)(i / rlt) % 2 == 0) // 偶数行
			{
				(i % rlt % 2 == 0) ? (currentColor = cWhite) : (currentColor = cBlack);
			}
			else // 奇数行
			{
				(i % rlt % 2 == 0) ? (currentColor = cBlack) : (currentColor = cWhite);
			}
		}
		cellColor->InsertNextTypedTuple(currentColor);
	}

	grid->GetCellData()->SetScalars(cellColor);
}

