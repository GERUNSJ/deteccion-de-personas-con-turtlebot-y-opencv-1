addpath('orig');

caja = int16(imread('10_depth_16_cajaytipo2_caja.png'));
tipo = int16(imread('10_depth_16_cajaytipo2_tipo.png'));

[x,y] = histograma(caja);

x_pos = x(65536:end);
y_pos = y(65536:end);

x_neg = x(1:65536);
y_neg = y(1:65536);

mean_pos = mean(x_pos.*y_pos);
std_pos = std(x_pos.*y_pos);

mean_neg = mean(x_neg.*y_neg);
std_neg = std(x_neg.*y_neg);

std_mean = mean([std_pos,std_neg]);

fprintf('Caja:\nPOS\tmedia = %f \t std = %f\nNEG\tmedia = %f \t std = %f\t std_mean = %f\n',...
    mean_pos,std_pos,mean_neg,std_neg,std_mean);

[x,y] = histograma(tipo);

x_pos = x(65536:end);
y_pos = y(65536:end);

x_neg = x(1:65536);
y_neg = y(1:65536);

mean_pos = mean(x_pos.*y_pos);
std_pos = std(x_pos.*y_pos);

mean_neg = mean(x_neg.*y_neg);
std_neg = std(x_neg.*y_neg);

std_mean = mean([std_pos,std_neg]);

fprintf('Tipo:\nPOS\tmedia = %f \t std = %f\nNEG\tmedia = %f \t std = %f\t std_mean = %f\n',...
    mean_pos,std_pos,mean_neg,std_neg,std_mean);
