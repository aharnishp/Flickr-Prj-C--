# Flickr Project Parser
This is subset of code files for our course in Social Network Analysis. 
This part of code is responsible for parsing the input graph of users on flicker, collected using Flickr API. It is optimised for extracting familiarity between users that have similarity in their selection of groups.

## Code Arcitecture
The main file inputs .csv files, and converts it to a temporary intermediate version to reduce memory requirements (converting strings to numbers, and also to test different logic faster by not ingesting full file sizes everytime) during processing time, and also optimised with map data structure to finds the bins faster.
This was re-written from scratch in C++ to use proper data structure and to reduce inefficient memory usage observed in previous python implementation (roughly 50x reduction in main memory requirement and 3x reduction in time).

## Results
![final_output](https://github.com/aharnishp/Flickr-Prj-Cpp/assets/69157507/3bf8ebf1-078b-410d-82b3-e84b49bef047)
The correlation between familiarity and similarity between users peeked when they shared 6 to 12 groups in common.
