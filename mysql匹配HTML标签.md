## mysql 匹配html标签
在数据库操作中，有时需要对html标签进行一些匹配查询、更新、删除操作，如果是简单的标签，我们直接将其
作为普通字符串就可以操作了，如：有表 test, 需要查找字段 name 中包含 table 标签的数据
```
DROP TABLE IF EXISTS `test`;
CREATE TABLE test(
	`id` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	`name` VARCHAR(500)
);
SELECT * FROM test WHERE name like '%<table%>%</table>%';
```
这样就能找出所有包含有完整 table 标签的数据

### mysql 删除html标签
mysql提供了正则表达式匹配查找,但是没有提供正则表达式替换的字符串操作函数;所以如果想要替换 html 标签,
就需要使用一些变通方法:
 首先,想要对字符串进行替换操作,第一个想到的是使用 replace 函数
```
REPLACE(str,from_str,to_str)
```
  返回字符串 str 并将其中所有子串 from_str 替换为 to_str; 其中 str 和 to_str 都是明确的,但是 from_str
我们只能知道是什么格式,具体是什么数据是无法知道,而且不同数据中,相匹配的部分也不尽相同.
- 解决办法: 使用 locate 定位,找到标签的头和尾,再用 substr 将其取出,如 table 标签
```
SELECT SUBSTR(name, 
  LOCATE('<table', name), 
  LOCATE('</table>', name) + CHAR_LENGTH('</table>')- LOCATE('<table', name))
FROM test WHERE name like '%<table%>%</table>';
```
这个方法是找到字符串中第一个 table 标签头出现的位置,和通过标签头尾的位置差计算出此标签的长度,从而取出子串;
但是这个方法有缺陷,只能找一层标签,如果是嵌套标签,那么不仅不能完全删除标签,而且会破坏标签结构比如:
``` 
123<table...>...<table...>...</table>xyz</table>456 
```
本来期望的结果是 ``` 123456 ``` 但是得到的结果却是 ``` 123xyz</table>456 ```
- 解决办法: 需要解决这个问题,就是要确定标签头和尾的匹配,在普通编程语言中,使用数据结构'栈'可以轻松解决,但这里是使用mysql语句如果想要在这里面进行操作,我至少现在还不知道如何进行; 那么只有换个思路,我们观察标签的结构,可以发现:嵌套的标签,最内层标签头尾是没有被其他标签隔断的,那么就可以想办法先找到最内层的标签,先将其删除,那么又会出现一个最内层标签,如此重复,就能一直正确删除到最外层的标签了,
- 怎么找到最内层的标签: 从开始找,找到的第一个标签尾,一定是一个最内层的标签,然后从这个位置反向找到的第一个标签头,必定是和他匹配的,这样就找到了一个正确完整的标签
- 如何反向寻找: mysql 的字符串定位中,没有直接的反向 locate 或类似的方法,但是其中有个方法 ``` reverse(str) ```, 其作用是将字符串 str 反序排列返回,如此,我们就可以将查找字符串和子字符串都反序,找到第一个匹配位置,然后通过计算就能得到反向查找的第一个匹配位置,这样就类似于上面的方法,可以取得一个正确完整的标签
```
SELECT SUBSTR(name, 
  LOCATE('</table>', name) - LOCATE(REVERSE('<table'), REVERSE(LEFT(name, LOCATE('</table>', name)))) + 2 - CHAR_LENGTH('<table'), 
  LOCATE('</table>', name) + CHAR_LENGTH('</table>')- (LOCATE('</table>', name) - LOCATE(REVERSE('<table'), REVERSE(LEFT(name, LOCATE('</table>', name)))) + 2 - CHAR_LENGTH('<table')))
FROM test WHERE name like '%<table%>%</table>'; 
```
