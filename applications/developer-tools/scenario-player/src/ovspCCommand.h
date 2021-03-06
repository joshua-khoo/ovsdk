/*********************************************************************
* Software License Agreement (AGPL-3 License)
*
* OpenViBE SDK Test Software
* Based on OpenViBE V1.1.0, Copyright (C) Inria, 2006-2015
* Copyright (C) Inria, 2015-2017,V1.0
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License version 3,
* as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>

#include <boost/optional.hpp>

#include "ovspICommand.h"

namespace OpenViBE
{
	/**
	* \struct InitCommand
	* \author cgarraud (INRIA)
	* \date 2016-01-26
	* \brief Command that drives the initialization of the tool
	* \ingroup ScenarioPlayer
	*
	* InitCommand class contains the following properties:
	* - Benchmark: Flag to enable benchmark on execute command (optional)
	* .
	*
	*/
	struct InitCommand : ICommand
	{
		// List of properties
		boost::optional<bool> benchmark;


		virtual PlayerReturnCode execute(KernelFacade& kernelFacade) const override;

	protected:

		virtual void doPrint(std::ostream& os) const override;
	};


	/**
	* \struct LoadKernelCommand
	* \author cgarraud (INRIA)
	* \date 2016-01-26
	* \brief Command that drives kernel loading
	* \ingroup ScenarioPlayer
	*
	* LoadKernelCommand contains the following properties:
	* - ConfigurationFile: Path to kernel configuration file (optional)
	* .
	*
	*/
	struct LoadKernelCommand : ICommand
	{
		// List of properties
		boost::optional<std::string> configurationFile;

		virtual PlayerReturnCode execute(KernelFacade& kernelFacade) const override;

	protected:

		virtual void doPrint(std::ostream& os) const override;
	};

	/**
	* \struct LoadScenarioCommand
	* \author cgarraud (INRIA)
	* \date 2016-01-26
	* \brief Command that drives scenario loading
	* \ingroup ScenarioPlayer
	*
	* LoadScenarioCommand contains the following properties:
	* - ScenarioFile: Path to xml scenario file (mandatory)
	* - ScenarioName: Name of the scenario (mandatory)
	* .
	*
	*/
	struct LoadScenarioCommand : ICommand
	{
		// List of properties
		boost::optional<std::string> scenarioFile;
		boost::optional<std::string> scenarioName;

		virtual PlayerReturnCode execute(KernelFacade& kernelFacade) const override;

	protected:

		virtual void doPrint(std::ostream& os) const override;
	};

	/**
	* \struct ResetCommand
	* \author cgarraud (INRIA)
	* \date 2016-01-26
	* \brief Command that drives tool reset to its initial state
	* \ingroup ScenarioPlayer
	*/
	struct ResetCommand : ICommand
	{

		virtual PlayerReturnCode execute(KernelFacade& kernelFacade) const override;

	protected:

		virtual void doPrint(std::ostream& os) const override;
	};

	/**
	* \struct RunScenarioCommand
	* \author cgarraud (INRIA)
	* \date 2016-01-26
	* \brief Command that drives the execution of a list of scenarios
	* \ingroup ScenarioPlayer
	*
	* RunScenarioCommand contains the following properties:
	* - ScenarioList: Names of scenario that must be executed (mandatory)
	* - PlayMode: 0 for standard, 1 for fastforward (optional)
	* - MaximumExecutionTime: Scenarios playing execution time limit (optional)
	* - TokenList: List of global (token,value) pairs (optional)
	* .
	*
	*/
	struct RunScenarioCommand : ICommand
	{

	public:

		using Token = std::pair<std::string, std::string>;

		// List of properties
		boost::optional<std::vector<std::string>> scenarioList;
		boost::optional<PlayerPlayMode> playMode;
		boost::optional<double> maximumExecutionTime;
		boost::optional<std::vector<Token>> tokenList;

		virtual PlayerReturnCode execute(KernelFacade& kernelFacade) const override;

	protected:

		virtual void doPrint(std::ostream& os) const override;
	};

	/**
	* \struct SetupScenarioCommand
	* \author cgarraud (INRIA)
	* \date 2016-01-26
	* \brief Command that drives the setup of a scenario
	* \ingroup ScenarioPlayer
	*
	* SetupScenarioCommand contains the following properties:
	* - ScenarioName: name of the scenario to setup (mandatory)
	* - TokenList: List of scenario specific tokens (optional)
	* .
	*
	* The token list overwrites the previous token list if the command was already
	* called on the same scenario (note that an empty token list is allowed).
	*
	*/
	struct SetupScenarioCommand : ICommand
	{

		using Token = std::pair<std::string, std::string>;

		// List of properties
		boost::optional<std::string> scenarioName;
		boost::optional<std::vector<Token>> tokenList;


		virtual PlayerReturnCode execute(KernelFacade& kernelFacade) const override;

	protected:

		virtual void doPrint(std::ostream& os) const override;
	};
}