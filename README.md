# Big-data-model-prediction

@[TOC](大数据模型预测实践（knn算法+词嵌入）)
# 前言
此次项目为根据北京大数据网站给出的用户信息和相应用户所游玩的景点，预测后续游客将要游玩的景点
由于数据集中许多标签为文字标签，故整体的技术方案为词嵌入+knn算法进行预测
预测效果为62%
# 词嵌入(Word Embedding)
词嵌入(Word Embedding)是一种将文本中的词转换成数字向量的方法，为了使用标准机器学习算法来对它们进行分析，就需要把这些被转换成数字的向量以数字形式作为输入。词嵌入过程就是把一个维数为所有词数量的高维空间嵌入到一个维数低得多的连续向量空间中，每个单词或词组被映射为实数域上的向量，词嵌入的结果就生成了词向量。
 
 目前主要的词嵌入技术有one-hot编码、Word2Vec（Word to Vector）、GloVe等等
 
 此次选择one hot编码进行词嵌入，One-hot编码(被称为独热码或独热编码)的词向量。One-hot编码是最基本的向量方法。One-hot编码通过词汇大小的向量表示文本中的词，其中只有对应于该词的项是1而所有其他的项都是零。
 
 具体实现代码若能理解one hot具体原理，便可轻易实现，且由于比较零碎，以上传至github->[https://github.com/BilboJunzhou/Big-data-model-prediction](https://github.com/BilboJunzhou/Big-data-model-prediction)
 便不一一讲述了
 
 变化效果如下：
 嵌入前
![嵌入前](https://img-blog.csdnimg.cn/d30a1f05ffe94fbeafc6dbfbc52f0f1b.png)
嵌入后
![嵌入后](https://img-blog.csdnimg.cn/4ffc17855f294c0fbc4f589a613affae.png)

  
# KNN算法
## 什么是KNN算法
邻近算法，或者说K最邻近（KNN，K-NearestNeighbor）分类算法是数据挖掘分类技术中最简单的方法之一。所谓K最近邻，就是K个最近的邻居的意思，说的是每个样本都可以用它最接近的K个邻近值来代表。近邻算法就是将数据集合中每一个记录进行分类的方法。

KNN算法的核心思想是，如果一个样本在特征空间中的K个最相邻的样本中的大多数属于某一个类别，则该样本也属于这个类别，并具有这个类别上样本的特性。该方法在确定分类决策上只依据最邻近的一个或者几个样本的类别来决定待分样本所属的类别。KNN方法在类别决策时，只与极少量的相邻样本有关。由于KNN方法主要靠周围有限的邻近的样本，而不是靠判别类域的方法来确定所属类别的，因此对于类域的交叉或重叠较多的待分样本集来说，KNN方法较其他方法更为适合。

这里尤其推荐一下B站智源学院的课程：[https://www.bilibili.com/video/BV1Nt411i7oD/?vd_source=7d1fabaa92959349756cbdc9e0be3e0e](https://www.bilibili.com/video/BV1Nt411i7oD/?vd_source=7d1fabaa92959349756cbdc9e0be3e0e)

听完之后绝对对KNN算法完全理解了

## 实现代码
此次代码基于python实现
```python
import csv
import random

with open('C:/Users/13747/Desktop/大数据比赛/predict.csv', 'r') as file:
    reader = csv.DictReader(file)
    predict = [row for row in reader]
# 读取训练数据
with open('C:/Users/13747/Desktop/大数据比赛/version.csv', 'r') as file:
    reader = csv.DictReader(file)
    datas = [row for row in reader]

random.shuffle(datas)
n = 100

test_set = datas[0:n]
train_set = datas[n:]

k = 10


def distance(d1, d2):
    res = 0
    for key in (
            'gender', '80', '70', '60', '90', '50', '40', '0', '20', '21~40', '41~60', '61~80', '1~20',
            '80~100', '5G',
            '4G', 'known', '3G', '2G', 'behavior1', 'behavior2', 'behavior31', 'behavior32', 'behavior33', 'empty',
            'A1', 'A2',
            'A3', 'A4', 'A5', 'A6', 'A7', 'A8', 'A9', 'A10', 'A11', 'A12', 'A13', 'A14', 'A15', 'A16', 'A17', 'A18',
            'A19',
            'A20', 'A21', 'A22', 'A23', 'A24', 'A25', 'A26', 'A27', 'A28', 'A29', 'A30', 'A31', 'A32', 'A33', 'A34',
            'A35',
            'A36', 'I1', 'I2', 'I3', 'I4', 'I5', 'I6', 'I7', 'I8', 'I9', 'I10', 'I11', 'I12', 'I13', 'I14', 'I15',
            'I16', 'I17',
            'I18', 'I19', 'I20', 'I21', 'I22', 'I23', 'I24', 'I25', 'I26', 'I27', 'I28', 'I29', 'I30', 'I31', 'I32'):
        res += (float(d1[key]) - float(d2[key])) ** 2
    return res ** 0.5


def knn(data):
    res = [
        {"result": train['label'], 'distance': distance(data, train)}
        for train in train_set
    ]
    res = sorted(res, key=lambda item: item['distance'])

    res2 = res[0:k]
    print(res2)
    result = {'1': 0, '2': 0, '3': 0, '4': 0, '5': 0, '6': 0, '7': 0}
    sum = 0
    for r in res2:
        sum += r['distance']

    for r in res2:
        if (sum):
            result[r['result']] += 1 - r['distance'] / sum
        else:
            result[r['result']] += 1 - r['distance']

    return max(result, key=result.get)


dicted = {'1': '景区类别1', '2': '景区类别2', '3': '景区类别3', '4': '景区类别4', '5': '景区类别5', '6': '景区类别6', '7': '景区类别7'}
a = len(predict)
print(a)
for i in range(a):
    name_of = dicted[knn(predict[i])]
    predict[i]['label'] = name_of

header = ['label','gender', '80', '70', '60', '90', '50', '40', '0', '20', '21~40', '41~60', '61~80', '1~20',
            '80~100', '5G',
            '4G', 'known', '3G', '2G', 'behavior1', 'behavior2', 'behavior31', 'behavior32', 'behavior33', 'empty',
            'A1', 'A2',
            'A3', 'A4', 'A5', 'A6', 'A7', 'A8', 'A9', 'A10', 'A11', 'A12', 'A13', 'A14', 'A15', 'A16', 'A17', 'A18',
            'A19',
            'A20', 'A21', 'A22', 'A23', 'A24', 'A25', 'A26', 'A27', 'A28', 'A29', 'A30', 'A31', 'A32', 'A33', 'A34',
            'A35',
            'A36', 'I1', 'I2', 'I3', 'I4', 'I5', 'I6', 'I7', 'I8', 'I9', 'I10', 'I11', 'I12', 'I13', 'I14', 'I15',
            'I16', 'I17',
            'I18', 'I19', 'I20', 'I21', 'I22', 'I23', 'I24', 'I25', 'I26', 'I27', 'I28', 'I29', 'I30', 'I31', 'I32']  # 数据列名
# -*- coding: utf-8 -*-
"""
Created on Tue Jul 10 22:06:43 2018
@author: User
"""

# print(predict[:,'A5'])

# test.csv表示如果在当前目录下没有此文件的话，则创建一个csv文件
# a表示以“追加”的形式写入，如果是“w”的话，表示在写入之前会清空原文件中的数据
# newline是数据之间不加空行
# encoding='utf-8'表示编码格式为utf-8，如果不希望在excel中打开csv文件出现中文乱码的话，将其去掉不写也行。

with open('C:/Users/13747/Desktop/大数据比赛/test.csv', 'a', newline='', encoding='utf-8') as f:
    writer = csv.DictWriter(f, fieldnames=header)  # 提前预览列名，当下面代码写入数据时，会将其一一对应。
    writer.writeheader()  # 写入列名
    writer.writerows(predict)  # 写入数据

```
