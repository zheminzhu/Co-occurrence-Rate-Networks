# Co-occurrence Rate Networks

*This verision is only for verifying the experimental results in the submitted paper. A more mature version will come soon. All rights of the datasets belong to their original authors.*

### Introduction
Co-occurrence rate networks are for sequence labeling tasks, such as named entity recognition, part-of-speech tagging … The applications of this software are similar to CRFs (http://crfpp.googlecode.com/svn/trunk/doc/index.html). But CRN can be trained much faster and obtain better or very competitive results.

### System and Compiler
The Ubuntu 12.04 and gcc 4.7.3 are used for compiling the software. We do not know  if this works on other systems. If your gcc is old version, you can update it using these steps to gcc 4.7.3:

1.	sudo add-apt-repository ppa:ubuntu-toolchain-r/test 
2.	sudo apt-get update 
3.	sudo apt-get install gcc-4.7
4.	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.6 
5.	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.7 40 --slave /usr/bin/g++ g++ /usr/bin/g++-4.7 
6.	sudo update-alternatives --config gcc

### Installation
1.	sudo make

### Usage
1.	./train train_file template_file model_folder
2.	./decode model_folder test_file result_file

### Using these commands to reproduce the experiments on NER datasets in the submitted paper:
1.	./train ./data/ner_en.train ./data/ner.template ./model/
2.	./decode ./model/ ./data/ner_en.testa testa.result
3.	./decode ./model/ ./data/ner_en.testb testb.result

### Data Format
Training and decoding data has the same format, see examples in the ./data. 

### Template Format
See example in the ./data for the template format.

### Contact
1.	Zhemin Zhu (z.zhu@utwente.nl, zhuzhemin@gmail.com)
2.	Djoerd Hiemstra (d.hiemstra@utwente.nl)
