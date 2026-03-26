% Read data from TXT file
% File format:
% Line 1: m b (slope and intercept)
% Line 2: A B (reference points)
% Lines 3+: x y (data points)

filename = 'datos.txt';  % Change this to your file name
data = dlmread(filename);

% Extract m and b from first row
m = data(1, 1);
b = data(1, 2);

% Extract A and B from second row
A = data(2, 1);
B = data(2, 2);

% Extract x and y data points (from row 3 onwards)
x_data = data(3:end, 1);
y_data = data(3:end, 2);

% Create x values for the theoretical line
x_line = min(x_data) - 1 : 0.1 : max(x_data) + 1;

% Compute theoretical y values
y_line = m * x_line + b;

% Plot the theoretical line
plot(x_line, y_line, 'b', 'LineWidth', 1)
hold on

% Plot the data points as black dots
plot(x_data, y_data, 'ko', 'MarkerSize', 1, 'MarkerFaceColor', 'k');

hold off
grid on
xlabel('x')
ylabel('y')
title(sprintf('y = %.2fx + %.2f (A=%.2f, B=%.2f)', m, b, A, B))
legend('Theoretical line', 'Data points')
