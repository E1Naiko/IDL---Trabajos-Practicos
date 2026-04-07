filename = 'datos.txt';
data = dlmread(filename, ';');

% m y b
m = data(1, 1);
b = data(1, 2);

% datos
x_data = data(2:end, 1);
y_data = data(2:end, 2);

x_line = min(x_data) - 1 : 0.1 : max(x_data) + 1;
y_line = m * x_line + b;

plot(x_line, y_line, 'b', 'LineWidth', 1)
hold on

plot(x_data, y_data, 'ko', 'MarkerSize', 5, 'MarkerFaceColor', 'k');

hold off
grid on
xlabel('x')
ylabel('y')
title(sprintf('y = %.2fx + %.2f', m, b))
legend('Linea real', 'Datos medidos')
