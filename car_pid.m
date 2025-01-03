% 資料 (時間, 角度, PWM)
filename = 'data.txt'; 
delimiter = ',';       % 資料使用逗號分隔
data = readmatrix('balance_car\data.txt', 'Delimiter', delimiter);

% 將時間起始調整為 0
time = data(:, 1) - data(1, 1);
angle = data(:, 2);
pwm = data(:, 3);

% 輸出資料 (角度)
output_data = angle;

% 輸入資料 (PWM)
input_data = pwm;

% 取樣時間 (假設取樣頻率固定，每10毫秒一筆資料，則取樣時間為 0.01 秒)
Ts = 0.01; % 秒

% 建立 iddata 對象
data_id = iddata(output_data, input_data, Ts);
sys = tfest(data_id, 3, 1);
% compare(sys, data_id)

C0 = pidstd(600, 0.0000000000000000000000000000000000000000000000001, 12);
[C, info] = pidtune(sys, C0);
%disp(C);
%disp(info);

sys_closed = feedback(C*sys, 1);
step(sys_closed);

% 若需要儲存為 MAT 檔案
% save('iddata.mat', 'data_id');

