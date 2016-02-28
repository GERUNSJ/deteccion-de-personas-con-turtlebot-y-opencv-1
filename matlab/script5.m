addpath('orig');

caja = int16(imread('caja16n.png'));
tipo = int16(imread('tipo16n.png'));

h = [-1,0,1];
gradiente = imfilter(double(caja),h);

g_pos = gradiente(gradiente>=0);
g_pos = g_pos(:);
g_neg = gradiente(gradiente<=0);
g_neg = g_neg(:);

std_pos = std(g_pos);
std_neg = std(g_neg);

mean_pos = mean(g_pos);
mean_neg = mean(g_neg);

std_mean = mean([std_pos,std_neg]);

fprintf('Caja:\nPOS\tmedia = %f \t std = %f\nNEG\tmedia = %f \t std = %f\t std_mean = %f\n',...
    mean_pos,std_pos,mean_neg,std_neg,std_mean);




gradiente = imfilter(double(tipo),h);

g_pos = gradiente(gradiente>=0);
g_pos = g_pos(:);
g_neg = gradiente(gradiente<=0);
g_neg = g_neg(:);

std_pos = std(g_pos);
std_neg = std(g_neg);

mean_pos = mean(g_pos);
mean_neg = mean(g_neg);

std_mean = mean([std_pos,std_neg]);

fprintf('Tipo:\nPOS\tmedia = %f \t std = %f\nNEG\tmedia = %f \t std = %f\t std_mean = %f\n',...
    mean_pos,std_pos,mean_neg,std_neg,std_mean);
