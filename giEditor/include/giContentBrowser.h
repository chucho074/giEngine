/**
 * @file    giContentBrowser.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    01/06/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giStdHeaders.h>
#include "giImGui.h"

using namespace giEngineSDK;
using namespace ImGui;

class ContentBrowser
{
 public:
	//Default constructor.
	ContentBrowser(Path inWorkingDir);
	
	//Default destructor.
	~ContentBrowser() = default;
	
	
	/**
	 * @brief      .
	 */
	void
	init();

	/**
	 * @brief      .
	 */
	void
	update(float inDeltaTime);

	/**
	 * @brief      .
	 */
	void 
	render();

	/**
	 * @brief      .
	 */
	void
	destroy();


	
 
 protected:
	

 private:

	 Path m_workingDirectory;

	 Path m_currentDirectory;
};