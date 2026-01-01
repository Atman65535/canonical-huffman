# 数据结构结课作业

tel: 13834627791

### 特性
- 哈夫曼编码树
- 范式编码树加速解压缩
- Yolov8 接口实现目标检测

曾尝试包合并算法解决最差情况下哈夫曼编码达到256位的情况，但是实际上编码长度远低于32位。于是忽略这个巨难，资料巨少的算法（之后有空研究），只使用范式编码树加速解压。

### 使用说明
本项目主要保留两个用户接口：huffman_coder和roi_huffman，除了这两部分接口cpp文件，请勿修改其他文件。否则无法运行需要自己debug。  

- huffman_coder：实现哈夫曼编码和解码的功能，用户可以通过命令行参数指定输入输出文件路径，实现对任意文件的压缩和解压缩。如果您的文件已经是压缩格式，如zip，jpg，则压缩无效。
- roi_huffman : 实现图像目标检测和裁剪压缩，如果您没有torch和cuda环境，可能无法使用。通过ultralytics的yolov8
  最佳实践：将roi huffman的可执行文件和detector文件夹置于同一个工作目录下，调用命令行使用
  环境配置：
~~~ sh
# 这个版本稳定，兼容mmlab系列推理
conda install pytorch==1.10.0 torchvision==0.11.0 torchaudio==0.10.0 cudatoolkit=11.3 -c pytorch -c conda-forge

# if this error happens:ImportError: /home/atman/opt/miniforge3/envs/mmdet/lib/python3.8/site-packages/torch/lib/libtorch_cpu.so: undefined symbol: iJIT_NotifyEvent

pip install mkl==2024.0

pip install ultralytics

~~~
> 当python脚本在c++里面被调用，cwd是c++的执行目录，所以我在脚本里面写死了运行目录在脚本目录，保证错误显式。所以请新建一个workdir，在里面存放c++可执行和python脚本文件夹detector，执行c++程序roi huffman

~~~bash
cd cmake-build-release
cmake ..
make -j 
./huffcode 
~~~
### 例子

~~~shell
cd workdir
conda activate mmdet # this is the environment that I used for inference.

# show huffman compression 
./huffcode compress ./test_text.txt ./test_text.txt.tlpress
# 50kb -> 31kb
./huffcode uncompress ./test_text.txt.tlpress ./test_text_uncompressed.txt
# show roi_huffman
./roi_huffman ./images.jpeg cat
~~~


### 注意事项
代码全部在ubuntu24上面实现，win平台需要考虑跨平台问题。如果需要验证，请使用cmake重新编译并把可执行文件放到对应位置。
推理部分需要GPU支持，如果推理失败，则请在roi huffman里面注释掉system调用python的部分，使用crops文件夹里面存留的图片。不过这个需要自己去改代码了，作者不考虑这个问题

### .tlpress 文件规约
文件头： 
uint32: magic number 商标，请勿修改。  
uint64：total symbol  
256 * uint8 编码长度表



