To make it work:
      the linux need to install chinese support
      follow CSDN post to combile python wrapper

Chinse support(Ref：https://blog.csdn.net/kevin6216/article/details/7530625)

      第一步，安装中文包：

      sudo apt-get install language-pack-zh*

      第二步，配置相关环境变量：

      sudo vim /etc/environment

      在文件中增加语言和编码的设置：

      LANG="zh_CN.UTF-8"
      LANGUAGE="zh_CN:zh:en_US:en"

      配置文件显示如下：
      PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games"
      LANG="zh_CN.UTF-8"
      UNZIP="-O CP936"
      ZIPINFO="-O CP936"

      第三步，重新设置本地配置：

      sudo dpkg-reconfigure locales





create Python Wrapper for TraderAPI(ref: https://blog.csdn.net/pjjing/article/details/77338423)

      第一步:sudo apt install swig 

      第二步，:swig -threads -c++ -python thosttraderapi.i 

      第三步，: create project "_thosttraderapi" in QT for python 2.7 in ubuntu linux 

      第四步，: compile the project and run test: pydemo_test.py
