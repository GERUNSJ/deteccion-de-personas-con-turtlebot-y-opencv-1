addpath('orig');

caja = int16(imread('10_depth_16_cajaytipo_caja.png'));
tipo = int16(imread('10_depth_16_cajaytipo_tipo.png'));

filtro = [-1,0,1];

caja_gradiente = imfilter(caja,filtro);
tipo_gradiente = imfilter(tipo,filtro);
% 
% caja_hist_gradiente = histogram(caja_gradiente,100, 'BinLimits',[1,10000]);
% tipo_hist_gradiente = histogram(tipo_gradiente,100, 'BinLimits',[1,10000]);

figure;
%imshow(caja_hist_gradiente);
caja_hist_gradiente = histogram(caja_gradiente,100, 'BinMethod','integers');
title('Caja1');
figure;
%imshow(tipo_hist_gradiente);
tipo_hist_gradiente = histogram(tipo_gradiente,100, 'BinMethod','integers');
title('Tipo1');

ch_values = caja_hist_gradiente.Values;
ch_values(1) = 0; % Eliminamos el negro
ch_values_tabla = ch_values.*[0:1:length(ch_values)-1];
fprintf('Caja:\tmedia = %f \t desviación = %f\n',mean(ch_values_tabla),std(ch_values_tabla));
% disp('Caja')
% disp('Media');
% mean(ch_values_tabla)
% disp('desviación');
% std(ch_values_tabla)

th_values = tipo_hist_gradiente.Values;
th_values(1) = 0; % Eliminamos el negro
th_values_tabla = th_values.*[0:1:length(th_values)-1];
fprintf('Tipo:\tmedia = %f \t desviación = %f\n',mean(th_values_tabla),std(th_values_tabla));
% disp('Tipo')
% disp('Media');
% mean(th_values_tabla)
% disp('desviación');
% std(th_values_tabla)

%-----------

caja = imread('10_depth_16_cajaytipo2_caja.png');
tipo = imread('10_depth_16_cajaytipo2_tipo.png');

filtro = [-1,0,1];

caja_gradiente = imfilter(caja,filtro);
tipo_gradiente = imfilter(tipo,filtro);
% 
% caja_hist_gradiente = histogram(caja_gradiente,100, 'BinLimits',[1,10000]);
% tipo_hist_gradiente = histogram(tipo_gradiente,100, 'BinLimits',[1,10000]);

figure;
%imshow(caja_hist_gradiente);
caja_hist_gradiente = histogram(caja_gradiente,100, 'BinLimits',[1,30000]);
title('Caja2');
figure;
%imshow(tipo_hist_gradiente);
tipo_hist_gradiente = histogram(tipo_gradiente,100, 'BinLimits',[1,30000]);
title('Tipo2');