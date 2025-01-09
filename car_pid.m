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

% 輸入資料 (0.1度)
input_data = 0.1 * ones(size(time));
%input_data = pwm;

% 取樣時間 (假設取樣頻率固定，每10毫秒一筆資料，則取樣時間為 0.01 秒)
sample_time = 0.01; % 秒

% 建立 iddata 對象
data_id = iddata(output_data, input_data, sample_time);

%Ts transfer function
Ts = tfest(input_data, output_data, 3, 'Ts', sample_time);

%compare 重和度
compare(Ts, data_id)

%PID origin
CO = pid(600, 0, 12, 'Ts', sample_time);

%反推物理系統
Tp = Ts / (CO * (1 - Ts));

%用practical 估算真的pid
[C, info] = pidtune(Ts, CO);
T_closed_loop = feedback(C * Ts, 1);

figure
step(T_closed_loop); % 模擬步階響應