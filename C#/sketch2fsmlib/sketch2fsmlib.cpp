// sketch2fsmlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

//#include "./../../SketchAnalyzer.h"
#include "sketch2fsmlib.h"

SketchAnalyzer* sa;

extern "C" {

	void Start()
	{
		sa = (SketchAnalyzer*)malloc(sizeof(SketchAnalyzer));
	}

	void LoadSketch(const char* t_path, int t_length)
	{
		sa->loadImage(t_path, t_length);
	}

	void FindConnectedComponents()
	{
		sa->findConnectedComponents();
	}

	void FindContainers()
	{
		sa->findContainers();
	}

	void FindCircles()
	{
		sa->findCircles();
	}

	void FindCharacters()
	{
		sa->findCharacters();
	}

	void FindArrows()
	{
		sa->findArrows();
	}

	void ParseLabels()
	{
		sa->parseLabels();
	}

	void CreateStates()
	{
		sa->createStates();
	}

	void CreateTransitions()
	{
		sa->createTransitions();
	}

	void OutputFile()
	{
		sa->outputFile();
	}
}