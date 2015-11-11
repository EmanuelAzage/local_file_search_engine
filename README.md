Author: Emanuel Azage
Date of last update: 11-9-15
Directory: ~/cs104/hw_eazage/hw6
USC ID: 5963 0530 39

Description:

This folder called hw6 contains two programs, crawler and search. crawler
takes in a configuration text file which includes a SEED_FILE parameter
representing the seed file for the data which search will be using to make
a search engine. search requires it's own configuration file which includes
the parameters for pagerank and the INDEX_FILE parameter representing the 
full list of files in the data set. This INDEX_FILE can be set the output 
of the crawler program, ../crawler_output.txt


Requirements:

The search program requires a folder containing the desired data set in the search directory.

The crawler program requires a folder containing the desired data set in the hw6 directory and this data folder 
should include a seed file. 


Instructions:

Step 1) crawler

	While inside the hw6 directory use the following command to compile the crawler program,
		g++ -g -Wall crawler.cpp -o crawler

	then use the following command to run the crawler program,
		./crawler config.txt

	optionally, you can run the crawler program without any command line arguments, this will use the default 
	configuration file that I have provided. 

Step 2) search
	
	While inside the search directory use the following commands to compile the search program,
		qmake
		make

	then use the following command to run the search program,
		./search configsearch.txt

	optionally, you can run the search program without any command line arguments, this will use the default 
	configuration file that I have provided.
