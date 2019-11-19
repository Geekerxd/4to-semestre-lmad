#include "Images.h"

using namespace Gdiplus;

Images::Images()
{
}

Images::~Images()
{
}

void Images::Load(WCHAR name[])
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR     gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	Bitmap* bitmap = new Bitmap(name);
	BitmapData* bitmapData = new BitmapData;

	_width = bitmap->GetWidth();
	_height = bitmap->GetHeight();

	Rect rect(0, 0, _width, _height);

	bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, bitmapData);

	unsigned char* pixels = (unsigned char*)bitmapData->Scan0;

	int size;
	size = _width * _height*4 ;
	//hagamos un try de la reserva de memoria
	try
	{
		_path = new unsigned char[size]; //[size*1000000]; ponganle esto como prueba
		_first = _path;
	}
	//en caso de falla entonces
	catch (std::exception& e)
	{
		//nosotros sabemos donde se genero el error entonces le diremos al usuario
		int msgboxID = MessageBox(hWnd, "Insuficiente memoria para contener la textura",
			TEXT("Clase Imagenes"), MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
		//interpretemos el message box y hagamos algo adecuado a la opcion seleccionada
		switch (msgboxID)
		{
			//de plano pa'juera o para afuera?, no me acuerdo!
		case IDCANCEL:
			exit(0);
			break;
			//un nuevo intento con una textura mas pequeño en todo caso
			//si no alcanza pa los tacos tonces pa la tortilla, que me pasa? ya comí?
		case IDTRYAGAIN:
			try {
				_path = new unsigned char[size];
				_first = _path;
			}
			catch (std::bad_alloc& e)
			{
				//en caso de no existir ni la menor pues algo mas se podra hacer.
			}
			break;
		case IDCONTINUE:
			//indicamos que continue si la textura y lo indicamos con nulo en el puntero para
			//que se interprete despues
			_path = NULL;
			_first = NULL;
			break;
		}

	}

	//tenemos que invertir el blue por el red
	//el green se conserva en posicion
	for (unsigned int i = 0; i < (_width * _height * 4); i += 4)
	{
		_path[i + 2] = pixels[i];
		_path[i + 1] = pixels[i + 1];
		_path[i] = pixels[i + 2];
		_path[i + 3] = pixels[i + 3];
	}

	bitmap->UnlockBits(bitmapData);

	delete bitmapData;
	delete bitmap;

	GdiplusShutdown(gdiplusToken);
}

void Images::Unload()
{
	delete[] _path;
}

unsigned char* Images::GetPath()
{
	return _first;
}

unsigned int Images::GetWidth()
{
	return _width;
}

unsigned int Images::GetHeight()
{
	return _height;
}
