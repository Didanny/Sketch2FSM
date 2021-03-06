// sketch2fsmlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "./../../SketchAnalyzer.h"
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

//sa.loadImage("./../../test2.jpg", 17);
//cv::imshow("SA IMG", sa.m_image_processor->originalImage());
//sa.findConnectedComponents();
////cv::imshow("SA Labels", sa.m_component_detector->getLabeledImage());
//sa.findContainers();
//sa.findCircles();
//sa.findCharacters();
//sa.findArrows();
//sa.parseLabels();
//sa.createStates();
//sa.createTransitions();
//sa.outputFile();