## 介绍

> 原项目地址：https://github.com/out0fmemory/nali

对比原本版本修改如下：

1. 单文件运行，不再依赖 `Perl`
2. 支持指定查询详细，通过 `-d` 选项来决定是否查看IP的公司归属，默认不显示
3. 不支持配合 `dig`、`cat`、`mtr`、`nslookup`、`traceroute`、`ping` 的管道使用

### 编译&安装&使用

```bash
git clone https://github.com/lurenJBD/nali.git
cd nali
./configure
make
make install
# 卸载
make uninstall
# 安装后更新 qqwry.dat
nali-update
```

> 安装的默认路径为：/usr/local/bin
>
> 纯真IP数据库 `qqwry.dat` 默认存放路径： /usr/local/share

### 运行示例

```bash
# 只查询IP地址
root@local:~/# nali 8.8.8.8
8.8.8.8[美国–加利福尼亚州–圣克拉拉–山景城]

# 查询IP地址和公司归属
root@local:~/# nali -d 8.8.8.8
8.8.8.8[美国–加利福尼亚州–圣克拉拉–山景城 谷歌公司DNS服务器]

# 支持同时查询多个IP
root@local:~/# nali -d 1.1.1.1 2606:4700:4700::1111
1.1.1.1[澳大利亚 APNIC/CloudFlare公共DNS服务器]
2606:4700:4700::1111[美国–弗吉尼亚州–劳登县–阿什本 Akamai节点]
```

### 单文件运行说明

在执行 `make` 后，可将 `bin/nali` 和 `share/qqwry.dat` 文件拷贝到其他系统的同一目录下使用，但不保证百分百可以运行，如果运行不了请尝试本机编译

### 关于纯真IP数据库 `qqwry.dat` 的来源

来自 https://github.com/FW27623/qqwry
