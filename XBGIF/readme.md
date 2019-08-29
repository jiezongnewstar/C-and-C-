###  使用android系统原生库加载gif

1. 了解GIF文件格式

2. 了解LZW算法

3. 使用libgif库实现gif文件播放

- 参考 [What's In A GIF](http://giflib.sourceforge.net/whatsinagif/bits_and_bytes.html "gif是什么")



---

#### 思考1，android已有gif图片加载框架（如glide），为什么我们还要去写原生native代码？

#### 思考2，java层代码如何实现加载gif？


好了，这两个问题一起来回答，无论是第三方图片加载框架，亦或者是java层代码实现，
避不开的一个问题就是内存占用问题，也就是性能问题，如果gif过大，则会出现OOM。

---

### GIF数据结构

    gif最多支持8位，及256色，前6个字节通常为“47 49 46 38 39 61” 或者 “47 49 46 37 61”对应的ASCII码为“GIF89a”或者“GIF87a”，表示GIF头（签名（前三位）+版本（后三位））

    ![](http://baidu.com/pic/doge.png)

==




