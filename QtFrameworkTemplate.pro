#声明本pro是做工程集目录的
TEMPLATE = subdirs

#brief:使用subdirs =a b c d声明的其实是4个子项的名字.默认你不多做说明的话,qmake根据名字自动去找子目录,启用子目录中的pro文件(名字优先匹配),这里可以看到使用了src，则会去src目录找寻pro文件
SUBDIRS = src
