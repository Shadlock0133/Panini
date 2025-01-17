/*
	MIT No Attribution

	Copyright 2021-2022 Mr. Hands

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to
	deal in the Software without restriction, including without limitation the
	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
	sell copies of the Software, and to permit persons to whom the Software is
	furnished to do so.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/

#pragma once

namespace panini
{
	/*!
		\enum BraceBreakingStyle
		\brief Brace breaking style to use when writing to output.
		\ingroup Globals
	*/
	enum class BraceBreakingStyle
	{
		Inherit,      //!< Inherit setting from the config, not valid on WriterBase
		Attach,       //!< Open brace on the same line
		Allman,       //!< New line before brace open
		Whitesmiths   //!< New line and indent before brace open and brace close
	};

	/*!
		\enum IncludeStyle
		\brief Include style to use when writing to output.
		\ingroup Globals
	*/
	enum class IncludeStyle
	{
		Inherit,         //!< Inherit setting from the config, not valid on WriterBase
		DoubleQuotes,    //!< Output double quotation marks ""
		SingleQuotes,    //!< Output single quotation marks '' (not valid for C++)
		AngularBrackets  //!< Output angular brackets <>
	};

	/*!
		\brief Global configuration applied to writers.

		Configuration is applied to all commands when they are processed by
		\ref WriterBase. Some commands can override these configuration
		settings in their constructor.
	*/
	struct Config
	{
		/*!
			The default brace breaking style to use for a writer.
		*/
		BraceBreakingStyle braceBreakingStyle = BraceBreakingStyle::Allman;

		/*!
			The default include style to use for a writer.
		*/
		IncludeStyle includeStyle = IncludeStyle::DoubleQuotes;

		/*!
			Chunk to output to indicate the end of a line.
		*/
		std::string chunkNewLine = "\n";

		/*!
			Chunk to output when indenting.
		*/
		std::string chunkIndent = "\t";
	};

};
