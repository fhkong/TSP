
T = 1000; %模拟退火的初始温度
X1 = 0:1:17;
X2 = 0:8:100;
X3 = 0:8:100;

f1 = 2.^X1;
f2 = T*X2;
f3 = X3.^2;

plot(X1,f1,'-.*r');
hold on;
plot(X2,f2,'-.*b');
hold on;
plot(X3,f3,'-.*g');
title('Time--N');
text(16,2^16,' \leftarrow 动态规划');
text(40,40000,' \leftarrow 模拟退火(T0=1000)');
text(80,80^2+9000, '\downarrow 贪心算法'); 

