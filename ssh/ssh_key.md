# ssh 秘钥

## 相关概念

### 原理
密匙认证需要依靠密匙，首先创建一对密匙（包括公匙和密匙，并且用公匙加密的数据只能用密匙解密），并把公匙放到需要远程服务器上。这样当登录远程 服务器时，客户端软件就会向服务器发出请求，请求用你的密匙进行认证。服务器收到请求之后，先在你在该服务器的宿主目录下寻找你的公匙，然后检查该公匙是 否是合法，如果合法就用公匙加密一随机数（即所谓的challenge）并发送给客户端软件。客户端软件收到 “challenge”之后就用私匙解密再把它发送给服务器。因为用公匙加密的数据只能用密匙解密，服务器经过比较就可以知道该客户连接的合法性。

### 加密方式
1. 对称加密(Symmetric Cryptography)

通过一个密钥进行数据的加密与解密操作。

对称加密是最快速、最简单的一种加密方式，加密（encryption）与解密（decryption）用的是同样的密钥（secret key）。对称加密有很多种算法，由于它效率很高，所以被广泛使用在很多加密协议的核心当中。

对称加密通常使用的是相对较小的密钥，一般小于256 bit。因为密钥越大，加密越强，但加密与解密的过程越慢。如果你只用1 bit来做这个密钥，那黑客们可以先试着用0来解密，不行的话就再用1解；但如果你的密钥有1 MB大，黑客们可能永远也无法破解，但加密和解密的过程要花费很长的时间。密钥的大小既要照顾到安全性，也要照顾到效率，是一个trade-off。

- DES（Data Encryption Standard）：数据加密标准，速度较快，适用于加密大量数据的场合
- 3DES（Triple DES）：是基于DES，对一块数据用三个不同的密钥进行三次加密，强度更高
- AES（Advanced Encryption Standard）：高级加密标准，是下一代的加密算法标准，速度快，安全级别高
> 2000年10月2日，美国国家标准与技术研究所（NIST--American National Institute of Standards and Technology）选择了Rijndael算法作为新的高级加密标准

对称加密的一大缺点是密钥的管理与分配，换句话说，如何把密钥发送到需要解密你的消息的人的手里是一个问题。在发送密钥的过程中，密钥有很大的风险会被黑客们拦截。现实中通常的做法是将对称加密的密钥进行非对称加密，然后传送给需要它的人。

2. 非对称加密(Asymmetric Cryptography)

非对称加密为数据的加密与解密提供了一个非常安全的方法，它使用了一对密钥，公钥（`public key`）和私钥（`private key`）。私钥只能由一方安全保管，不能外泄，而公钥则可以发给任何请求它的人。非对称加密使用这对密钥中的一个进行加密，而解密则需要另一个密钥。比如，你向银行请求公钥，银行将公钥发给你，你使用公钥对消息加密，那么只有私钥的持有人--银行才能对你的消息解密。与对称加密不同的是，银行不需要将私钥通过网络发送出去，因此安全性大大提高。

目前最常用的非对称加密算法是RSA算法，是Rivest, Shamir, 和Adleman于1978年发明，他们那时都是在MIT。

- RSA
- DSA
- ECC

## 如何生成密匙
### ssh-keygen
```
usage: ssh-keygen [options]
Options:
  -A          Generate non-existent host keys for all key types.
  -a number   Number of KDF rounds for new key format or moduli primality tests.
  -B          Show bubblebabble digest of key file.
  -b bits     Number of bits in the key to create.
  -C comment  Provide new comment.
  -c          Change comment in private and public key files.
  -D pkcs11   Download public key from pkcs11 token.
  -e          Export OpenSSH to foreign format key file.
  -F hostname Find hostname in known hosts file.
  -f filename Filename of the key file.
  -G file     Generate candidates for DH-GEX moduli.
  -g          Use generic DNS resource record format.
  -H          Hash names in known_hosts file.
  -h          Generate host certificate instead of a user certificate.
  -I key_id   Key identifier to include in certificate.
  -i          Import foreign format to OpenSSH key file.
  -J number   Screen this number of moduli lines.
  -j number   Start screening moduli at specified line.
  -K checkpt  Write checkpoints to this file.
  -k          Generate a KRL file.
  -L          Print the contents of a certificate.
  -l          Show fingerprint of key file.
  -M memory   Amount of memory (MB) to use for generating DH-GEX moduli.
  -m key_fmt  Conversion format for -e/-i (PEM|PKCS8|RFC4716).
  -N phrase   Provide new passphrase.
  -n name,... User/host principal names to include in certificate
  -O option   Specify a certificate option.
  -o          Enforce new private key format.
  -P phrase   Provide old passphrase.
  -p          Change passphrase of private key file.
  -Q          Test whether key(s) are revoked in KRL.
  -q          Quiet.
  -R hostname Remove host from known_hosts file.
  -r hostname Print DNS resource record.
  -S start    Start point (hex) for generating DH-GEX moduli.
  -s ca_key   Certify keys with CA key.
  -T file     Screen candidates for DH-GEX moduli.
  -t type     Specify type of key to create.
  -u          Update KRL rather than creating a new one.
  -V from:to  Specify certificate validity interval.
  -v          Verbose.
  -W gen      Generator to use for generating DH-GEX moduli.
  -y          Read private key file and print public key.
  -Z cipher   Specify a cipher for new private key format.
  -z serial   Specify a serial number.
```

通常使用只需要指定加密方式 `-t`，或者加上一个注释内容 `-C`
```
ssh-keygen -t rsa -C "myemail"
```
之后按默认生成，直接回车，密码为空，会在 `~/.ssh/` 目录下生成两个文件:
`id_rsa.pub`(公钥) 和 `id_rsa`(私钥)

在生成的密钥中，包含了机器唯一码，加密解密用密钥字符串，注释信息这三部分信息。

## 使用密钥无密码登录
单向登陆的操作过程（机器A无需密码登录到机器B）：
1. 登录A机器
1. ssh-keygen -t [rsa|dsa]，将会生成密钥文件和私钥文件 id_rsa,id_rsa.pub或id_dsa,id_dsa.pub
1. 将 .pub 文件复制到B机器的 ~/.ssh 目录，并 cat id_dsa.pub >> ~/.ssh/authorized_keys
1. 大功告成，从A机器登录B机器的目标账户，不再需要密码了；（直接运行 #ssh B_ip）

双向登陆的操作过程：
ssh-keygen做密码验证可以使在向对方机器上ssh，scp不用使用密码.具体方法如下:
1. 两个节点都执行操作：#ssh-keygen -t rsa 然后全部回车,采用默认值.
1. 这样生成了一对密钥，存放在用户目录的~/.ssh下。
1. 将公钥考到对方机器的用户目录下，并将其复制到~/.ssh/authorized_keys中
1. 设置文件和目录权限：
```
//设置authorized_keys权限
$ chmod 600 authorized_keys
//设置.ssh目录权限
$ chmod 700 -R .ssh
```
1. 要保证.ssh和authorized_keys都只有用户自己有写权限。否则验证无效。
