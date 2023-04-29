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
