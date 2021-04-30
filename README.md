# Mini_C
简单的类C语言编译器
# 1 目录结构  
## 1.1 头文件  
### 1.1.1 MFC框架头文件  
framework.h  MFC框架文件  
Mini_C.h  应用程序的主头文件  
Mini_CDlg.h  程序主对话框的类  
Resource.h  MFC资源文件  
targetver.h  MFC框架文件  
grammer_analysis_dialog.h  输出语法树的子对话框的类  
word_analysis_dialog.h  输出词法分析结果的子对话框的类  

### 1.1.2 自创头文件  
word_analysis  词法分析类  
grammer_analysis  语法分析类  

## 1.2 cpp文件
### 1.2.1 MFC实现文件  
grammer_analysis_dialog.cpp  此文件是显示语法树的子对话框的实现文件  
word_analysis_dialog.cpp  此文件是显示词法分析结果的子对话框的实现文件  
Mini_C.cpp  定义应用程序的类行为  
Mini_CDlg.cpp  此类是主对话框的实现文件  

### 1.2.2 自创头文件的实现文件
word_analysis.cpp  词法分析实现  
grammer_analysis.cpp  语法分析实现  

## 1.3 测试文件  
test2.txt  

# 2 已完成的功能  
词法分析：把代码中的单词提取出来，并且能够识别它对应的类型。  
语法分析：输出语法树  

# 3 实现思路  
用判断树的思想进行词法分析，将token和对应的标签分别用一个vector存起来，使用只读的Edit Control控件输出词法分析结果。使用递归下降分析法实现语法树的分析。使用MFC的CTreeCtrl控件在图形界面实现语法树的输出。  

# 4 测试展示
![image1](https://github.com/Gao-JF/Mini_C/blob/main/1.png?raw=true)  
![image2](https://github.com/Gao-JF/Mini_C/blob/main/2.png?raw=true)







