#pragma once
#include "Manejador.h"
#include "SatelliteList.h"
#include "SatelliteListIterator.h""
#include "TspFile.h"
#include "Crossover.h"
#include "Poblacion.h"
#include "Opt2.h"
#include <string>
#include <vector>
#include <iterator>  // para std::back_inserter



namespace CppCLRWinformsProjekt {
	

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;


	
	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{




	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ archivoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ cargarToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ejecutarToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ToolStripMenuItem^ randomico2ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ randomicoCercania2ptosToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ eAXToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ islasToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ evolucionarToolStripMenuItem;


	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->archivoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cargarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ejecutarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->randomico2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->randomicoCercania2ptosToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eAXToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->islasToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->evolucionarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L" \"Archivos de TSP|*.tsp|Todos|*.*\"";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->archivoToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(720, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// archivoToolStripMenuItem
			// 
			this->archivoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->cargarToolStripMenuItem,
					this->ejecutarToolStripMenuItem, this->eAXToolStripMenuItem, this->islasToolStripMenuItem, this->evolucionarToolStripMenuItem
			});
			this->archivoToolStripMenuItem->Name = L"archivoToolStripMenuItem";
			this->archivoToolStripMenuItem->Size = System::Drawing::Size(60, 20);
			this->archivoToolStripMenuItem->Text = L"Archivo";
			this->archivoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::archivoToolStripMenuItem_Click);
			// 
			// cargarToolStripMenuItem
			// 
			this->cargarToolStripMenuItem->Name = L"cargarToolStripMenuItem";
			this->cargarToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->cargarToolStripMenuItem->Text = L"Cargar .tsp";
			this->cargarToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::cargarToolStripMenuItem_Click);
			// 
			// ejecutarToolStripMenuItem
			// 
			this->ejecutarToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->randomico2ToolStripMenuItem,
					this->randomicoCercania2ptosToolStripMenuItem
			});
			this->ejecutarToolStripMenuItem->Name = L"ejecutarToolStripMenuItem";
			this->ejecutarToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->ejecutarToolStripMenuItem->Text = L"Ejecutar Greedy";
			// 
			// randomico2ToolStripMenuItem
			// 
			this->randomico2ToolStripMenuItem->Name = L"randomico2ToolStripMenuItem";
			this->randomico2ToolStripMenuItem->Size = System::Drawing::Size(247, 22);
			this->randomico2ToolStripMenuItem->Text = L"salida Randomico";
			this->randomico2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::randomico2ToolStripMenuItem_Click);
			// 
			// randomicoCercania2ptosToolStripMenuItem
			// 
			this->randomicoCercania2ptosToolStripMenuItem->Name = L"randomicoCercania2ptosToolStripMenuItem";
			this->randomicoCercania2ptosToolStripMenuItem->Size = System::Drawing::Size(247, 22);
			this->randomicoCercania2ptosToolStripMenuItem->Text = L"salida Randomico cercania 2ptos";
			this->randomicoCercania2ptosToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::randomicoCercania2ptosToolStripMenuItem_Click);
			// 
			// eAXToolStripMenuItem
			// 
			this->eAXToolStripMenuItem->Name = L"eAXToolStripMenuItem";
			this->eAXToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->eAXToolStripMenuItem->Text = L"CiclosAB";
			this->eAXToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::eAXToolStripMenuItem_Click);
			// 
			// islasToolStripMenuItem
			// 
			this->islasToolStripMenuItem->Name = L"islasToolStripMenuItem";
			this->islasToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->islasToolStripMenuItem->Text = L"Islas";
			this->islasToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::islasToolStripMenuItem_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 49);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(720, 423);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(0, 478);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(720, 59);
			this->textBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(178, 33);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(16, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"...";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// evolucionarToolStripMenuItem
			// 
			this->evolucionarToolStripMenuItem->Name = L"evolucionarToolStripMenuItem";
			this->evolucionarToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->evolucionarToolStripMenuItem->Text = L"Evolucionar";
			this->evolucionarToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::evolucionarToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(720, 533);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Computación Evolutiva de Alto Rendimiento, TSP ";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void abrirToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ejecutarToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void archivoToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}


	private: System::Void cargarToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			//  obtener la ruta del archivo seleccionado.
			String^ filePath = this->openFileDialog1->FileName;
			IntPtr pointer = Marshal::StringToHGlobalAnsi(filePath);
			char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
			std::string unmanagedString = charPointer;
			Marshal::FreeHGlobal(pointer);
			
            TspFile tspFile = TspFile(unmanagedString);
			this->textBox1->AppendText("Archivo cargado..."+ filePath + Environment::NewLine);
			label1->Text = filePath;
			drawCities(this->pictureBox1, tspFile);


		}
	}


private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
}
	   void drawCities(System::Windows::Forms::PictureBox^ pictureBox, TspFile& tspFile) {
		   System::Drawing::Graphics^ g = pictureBox->CreateGraphics();
		   g->Clear(System::Drawing::Color::White);
		   System::Drawing::Brush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);

		   int maxX = tspFile.getMaxX();
		   int maxY = tspFile.getMaxY();
		   int minX = tspFile.getMinX();
		   int minY = tspFile.getMinY();

		   double scaleX = (pictureBox->Width - 10.0) / (maxX - minX); // -10 para un poco de margen
		   double scaleY = (pictureBox->Height - 10.0) / (maxY - minY); // -10 para un poco de margen

		   std::vector<Point2D> cities = tspFile.getSetCities();
		   for (Point2D point : cities) {
			   int radius = 4;
			   int scaledX = (point.x - minX) * scaleX + 5; // +5 para un poco de margen
			   //int scaledY = (point->y - minY) * scaleY + 5; // +5 para un poco de margen
			   int scaledY = pictureBox->Height - ((point.y - minY) * scaleY + 5); // Invierte la coordenada y
			   g->FillEllipse(brush, scaledX - radius, scaledY - radius, radius * 2, radius * 2);
		   }

		   delete brush;
		   delete g;
	   }






	   void drawCitiesAndSegments(System::Windows::Forms::PictureBox^ pictureBox, TspFile& tspFile,  SatelliteList tour) {
		   System::Drawing::Graphics^ g = pictureBox->CreateGraphics();
		   g->Clear(System::Drawing::Color::White);
		   System::Drawing::Brush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);

		   int maxX = tspFile.getMaxX();
		   int maxY = tspFile.getMaxY();
		   int minX = tspFile.getMinX();
		   int minY = tspFile.getMinY();

		   double scaleX = (pictureBox->Width - 10.0) / (maxX - minX);
		   double scaleY = (pictureBox->Height - 10.0) / (maxY - minY);

		   std::vector<Point2D> cities = tspFile.getSetCities();

		   // Dibujar los puntos
		   for (Point2D point : cities) {
			   int radius = 4;
			   int scaledX = (point.x - minX) * scaleX + 5;
			   int scaledY = pictureBox->Height - ((point.y - minY) * scaleY + 5);
			   g->FillEllipse(brush, scaledX - radius, scaledY - radius, radius * 2, radius * 2);
		   }



		   

		   for (const Point2D punto : cities) {
			   if (punto.x < minX) minX = punto.x;
			   if (punto.x > maxX) maxX = punto.x;
			   if (punto.y < minY) minY = punto.y;
			   if (punto.y > maxY) maxY = punto.y;
		   }

		   SatelliteListIterator iterator(&tour);
		   Point2D primerNodo=iterator.next();
		   Point2D actualNodo = primerNodo;
		   int cantIteraciones = 1;
		   while 	(iterator.hasNext()){
			   cantIteraciones++;												   // Dibujar los segmentos de línea
			   Point2D siguienteNodo = iterator.next();
			   int scaledStartX = (actualNodo.x - minX) * scaleX + 5;
			   int scaledStartY = pictureBox->Height - ((actualNodo.y - minY) * scaleY + 5);
			   int scaledEndX = (siguienteNodo.x - minX) * scaleX + 5;
			   int scaledEndY = pictureBox->Height - ((siguienteNodo.y - minY) * scaleY + 5);
			   float ancho = 3.0f; // Ancho de la línea
			   g->DrawLine(gcnew System::Drawing::Pen(System::Drawing::Color::Green, ancho), scaledStartX, scaledStartY, scaledEndX, scaledEndY);
			   actualNodo = siguienteNodo;
		   }

		   // Cerrar el tour conectando el último punto con el primero
		   int scaledStartX = (actualNodo.x - minX) * scaleX + 5;
		   int scaledStartY = pictureBox->Height - ((actualNodo.y - minY) * scaleY + 5);
		   int scaledEndX = (primerNodo.x - minX) * scaleX + 5;
		   int scaledEndY = pictureBox->Height - ((primerNodo.y - minY) * scaleY + 5);

		   float ancho = 3.0f; // Ancho de la línea
		   g->DrawLine(gcnew System::Drawing::Pen(System::Drawing::Color::Green, ancho), scaledStartX, scaledStartY, scaledEndX, scaledEndY);
		  
		   //this->textBox1->AppendText("Iterador tour..." + cantIteraciones.ToString() + Environment::NewLine);

		   delete brush;
		   delete g;
	   }




private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	IntPtr pointer = Marshal::StringToHGlobalAnsi(label1->Text);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string unmanagedString = charPointer;
	Marshal::FreeHGlobal(pointer);
	TspFile tspFile = TspFile(unmanagedString);
	Manejador manejador(tspFile);
	manejador.createInitialPath();

	drawCitiesAndSegments(this->pictureBox1, tspFile, manejador.initialPath);


	
}
private: System::Void randomico2ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	IntPtr pointer = Marshal::StringToHGlobalAnsi(label1->Text);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string unmanagedString = charPointer;
	Marshal::FreeHGlobal(pointer);
	TspFile tspFile = TspFile(unmanagedString);
	Manejador manejador(tspFile);
	if(manejador.createInitialPath()) {

	drawCitiesAndSegments(this->pictureBox1, tspFile, manejador.initialPath);
	}
}
private: System::Void randomicoCercania2ptosToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	IntPtr pointer = Marshal::StringToHGlobalAnsi(label1->Text);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string unmanagedString = charPointer;
	Marshal::FreeHGlobal(pointer);
	TspFile tspFile = TspFile(unmanagedString);
	Manejador manejador(tspFile);

	if(manejador.createInitialPath2Ptos()) {
	drawCitiesAndSegments(this->pictureBox1, tspFile, manejador.initialPath);
	}
}
private: System::Void eAXToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	IntPtr pointer = Marshal::StringToHGlobalAnsi(label1->Text);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string unmanagedString = charPointer;
	Marshal::FreeHGlobal(pointer);
	TspFile tspFile = TspFile(unmanagedString);
	Manejador manejador(tspFile);
	SatelliteList padre1;
	SatelliteList padre2;

	if (manejador.createInitialPath()) {
		padre1 = manejador.initialPath;
		drawCitiesAndSegments(this->pictureBox1, tspFile, manejador.initialPath);
	}

	Thread::Sleep(2000);   // El tiempo se da en milisegundos


	if (manejador.createInitialPath()) {
		padre2 = manejador.initialPath;
		drawCitiesAndSegments(this->pictureBox1, tspFile, manejador.initialPath);
	}

	Thread::Sleep(1000);   // El tiempo se da en milisegundos
	Crossover cruce;
	//SatelliteList hijo =cruce.cruzar(padre1, padre2,manejador.nearestNeighbors);
	std::vector<Segmento> ciclos= cruce.getCiclosAB(padre1, padre2, manejador.nearestNeighbors);
	drawCitiesAndSegments(this->pictureBox1, tspFile, ciclos);
}


	   void drawCitiesAndSegments(System::Windows::Forms::PictureBox^ pictureBox, TspFile& tspFile, std::vector<Segmento> segmentos) {
		   System::Drawing::Graphics^ g = pictureBox->CreateGraphics();
		   g->Clear(System::Drawing::Color::White);
		   System::Drawing::Brush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);

		   int maxX = tspFile.getMaxX();
		   int maxY = tspFile.getMaxY();
		   int minX = tspFile.getMinX();
		   int minY = tspFile.getMinY();

		   double scaleX = (pictureBox->Width - 10.0) / (maxX - minX);
		   double scaleY = (pictureBox->Height - 10.0) / (maxY - minY);

		   std::vector<Point2D> cities = tspFile.getSetCities();

		   // Dibujar los puntos
		   for (Point2D point : cities) {
			   int radius = 4;
			   int scaledX = (point.x - minX) * scaleX + 5;
			   int scaledY = pictureBox->Height - ((point.y - minY) * scaleY + 5);
			   g->FillEllipse(brush, scaledX - radius, scaledY - radius, radius * 2, radius * 2);
		   }



		   // Dibujar los segmentos
		   for (Segmento seg : segmentos) {
			   Point2D start = cities[seg.nodo_anterior]; // Acceso directo por índice
			   Point2D end = cities[seg.nodo_siguiente];  // Acceso directo por índice


			   int scaledStartX = (start.x - minX) * scaleX + 5;
			   int scaledStartY = pictureBox->Height - ((start.y - minY) * scaleY + 5);
			   int scaledEndX = (end.x - minX) * scaleX + 5;
			   int scaledEndY = pictureBox->Height - ((end.y - minY) * scaleY + 5);

			   float ancho = 3.0f; // Ancho de la línea
			   System::Drawing::Color color = seg.es_padre_A ? System::Drawing::Color::Green : System::Drawing::Color::Blue;
			   g->DrawLine(gcnew System::Drawing::Pen(color, ancho), scaledStartX, scaledStartY, scaledEndX, scaledEndY);
		   }

		   delete brush;
		   delete g;
	   }



private: System::Void islasToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	IntPtr pointer = Marshal::StringToHGlobalAnsi(label1->Text);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string unmanagedString = charPointer;
	Marshal::FreeHGlobal(pointer);
	TspFile tspFile = TspFile(unmanagedString);
	Manejador manejador(tspFile);
	SatelliteList padre1;
	SatelliteList padre2;

	if (manejador.createInitialPath()) {
		padre1 = manejador.initialPath;
		drawCitiesAndSegments(this->pictureBox1, tspFile, manejador.initialPath);
	}

	Thread::Sleep(2000);   // El tiempo se da en milisegundos


	if (manejador.createInitialPath()) {
		padre2 = manejador.initialPath;
		drawCitiesAndSegments(this->pictureBox1, tspFile, manejador.initialPath);
	}

	Thread::Sleep(2000);

	CiclosABGenerator generador;
	std::vector<CicloAB> ciclosAB = generador.generarCiclosAB(padre1, padre2);
	
	std::vector<Segmento> coleccionDeSegmentos;

	for (const CicloAB& ciclo : ciclosAB) {
		std::copy(ciclo.segmentos.begin(), ciclo.segmentos.end(), std::back_inserter(coleccionDeSegmentos));
	}



	drawCitiesAndSegments(this->pictureBox1, tspFile, coleccionDeSegmentos);

	Thread::Sleep(2000);   // El tiempo se da en milisegundos
	Crossover cruce;
	
	std::vector<Segmento> miniToursPadre1 = padre1.divideTourConCiclosAB(ciclosAB);
	drawCitiesAndSegments(this->pictureBox1, tspFile, miniToursPadre1);
	

	Thread::Sleep(2000);   // El tiempo se da en milisegundos
	SatelliteList tour = cruce.unionDeSegmentos(miniToursPadre1, manejador.nearestNeighbors, tspFile);
	drawCitiesAndSegments(this->pictureBox1, tspFile, tour);
}





private: System::Void evolucionarToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	IntPtr pointer = Marshal::StringToHGlobalAnsi(label1->Text);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string unmanagedString = charPointer;
	Marshal::FreeHGlobal(pointer);
	TspFile tspFile = TspFile(unmanagedString);
	Manejador manejador(tspFile);
	
	Poblacion poblacion;
	long generaciones = 20;

	Opt2 opt2;

	while(poblacion.tours.size()< poblacion.cantIndividuos){
		SatelliteList padre= manejador.createGreedy2ptosPath();
		poblacion.insertar(padre);
		padre = manejador.createGreedyPath();
		poblacion.insertar(padre);
	}
	

	for (long i = 0; i < generaciones; i++)
	{

		for (int i = 0; i < poblacion.cantIndividuos-1; i++)
		{
			SatelliteList tourAmejorar = poblacion.tours[i];
			tourAmejorar.getFitness();
			std::pair<SatelliteList, bool> resultado = opt2.localOpt2(tourAmejorar,manejador.nearestNeighbors);
			if (resultado.second == true) {
				resultado.first.getFitness();
				poblacion.insertar(resultado.first);
                SatelliteList mejorIndividuo = poblacion.mejorIndividuo();
	            drawCitiesAndSegments(this->pictureBox1, tspFile, mejorIndividuo);
	            Thread::Sleep(10);
			}
		}


        poblacion.eliminarPeores();//siempre eliminar despues del opt2 
		std::pair<SatelliteList, SatelliteList>  seleccionados=poblacion.seleccion();
		Crossover cruce;
		SatelliteList individuoHijo=cruce.cruzar(seleccionados.first, seleccionados.second, manejador.nearestNeighbors, tspFile);
		poblacion.insertar(individuoHijo);
		
		long mejorFitness = poblacion.mejorIndividuo().getFitness();
		this->textBox1->AppendText("Fitness =" + mejorFitness.ToString() + "Generacion." + i.ToString() + Environment::NewLine);
	   
    }


	

}
};



}
