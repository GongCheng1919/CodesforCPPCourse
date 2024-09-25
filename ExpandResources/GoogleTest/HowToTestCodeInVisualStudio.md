<center>如何测试代码</center>
# 为什么要使用gtest
在日常学习开发中，我们往往会遇到下面的一些错误。
* 数组越界
* 整数溢出
* 浮点数精度损失
* 代码运行结果与预期不匹配
如果你依然只会在VisualStudio当中 ``Ctrl+F5`` 然后``Ctrl CV`` 之后观察输出。或者只会在程序中间插入 ``cout`` 来观察中间运行结果那么也许这篇教程能给你一个不一样的启发和思考。


举个使用gtest检测手动实现一个计算器原理的例子，这里我们只考虑将中缀表达式转换为后缀表达式的部分。

# gtest环境配置

1.首先新建一个空项目

![](./image/Pasted%20image%2020240925220637.png)


2.在项目中添加 ``include``和``src``文件分别用于存储头文件和源代码文件

![](./image/Pasted%20image%2020240925220752.png)
3.导入相应的头文件和源文件
![](./image/Pasted%20image%2020240925224229.png)


4.接着右击==解决方案==，创建新项目
![](./image/Pasted%20image%2020240925224352.png)


5.在项目界面选择GoogleTest 重新创建一个项目，配置保持默认即可
![](./image/Screenshot%202024-09-25%20224426.png)
![](./image/Screenshot%202024-09-25%20224444.png)


6.创建好之后项目结构如下，此时需要将test项目设置为启动项目，然后将Calculator项目的头文件添加到test项目的路径当中
![[Pasted image 20240925235406.png]]


![](./image/GoogleTest.gif)


7.接着就可以在test.cpp当中编写测试代码

这里我们测试能否将“1+2+3+4+5”转变为后缀表达式。
![](./image/Pasted%20image%2020240926001036.png)

在最下面我们可以看到自己通过的样例数目，这里我们一个样例都没有通过。
![](./image/Pasted%20image%2020240926001258.png)

然后我们选取其中一个样例观察，观察到我们的输入和输出之间存在的差别
![](./image/Pasted%20image%2020240926001354.png)

这样方便我们监测自己代码是否能够正常工作或者是达到预期。


# 参考资源‘

[gtest编写教程](https://github.com/AngryHacker/articles/blob/master/src/open_source_components/google_gtest.md)

[GTest / GMock 单元测试实践手册](https://imageslr.com/2023/gtest.html#%E4%BA%8Chello-world%E4%BB%8E%E4%B8%80%E4%B8%AA%E5%8D%95%E6%B5%8B%E7%A4%BA%E4%BE%8B%E5%BC%80%E5%A7%8B)





