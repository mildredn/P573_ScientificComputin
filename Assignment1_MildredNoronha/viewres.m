%
% Rough script for analysis of the vector timing data for P573,
% Fall 2017. 
%
% Put this script (named viewres.m) in the same directory as the output file
% "results" from the first assignment. Start Matlab however you want:
%   1. in a terminal window, just type the command "matlab", OR
%   2. go to the start menu in your window manager, hunt down where Matlab is,
%       and click that button.
% In the command window of the GUI, at the prompt type "viewres", the name of
% this script without the .m suffix. Then it should slurp in the timings file,
% compute the computational rates, and plot them.
% 
% Started: Wed 04 Oct 2017, 07:38 AM
% Last Modified: Wed 04 Oct 2017, 07:38 AM
%-----------------

base0 = false; % If true, force y-axis to have min at 0

if ~exist('results', 'file')
    disp('Cannot find the input file named "results". Make sure it is in the same')
    disp('directory as this script, then try again.')
    return
end

G = load('results');
% G should have 4 columns in it, and number of rows = number of timings made.
% Next, split G out by columns, assigning the columns to variables with more
% meaningful names.

n    = G(:,1); 
t    = G(:,2);
reps = G(:,3);
op   = G(:,4);

I1 = find(op == 1);  % I1 has the row numbers in G corr to 1-norm
norm_1 = 2.0e-9*n(I1)./t(I1); % Gflops/sec for the first vec op.

I2 = find(op == 2);  % I2 has the row numbers in G corr to norm_2
norm_2 = 2.0e-9*n(I2)./t(I2);  % Gflops/sec for the second vec op.

I3 = find(op == 3);  % I3 has the row numbers in G corr to norm_inf
norm_inf = 2.0e-9*n(I3)./t(I3); % Gflops/sec for the third vec op.

plot(n(I1), norm_1, 'b+-', ...
     n(I2), norm_2, 'r*-', ...
     n(I3), norm_inf, 'go-')

if base0
    a = axis;
    axis([a(1:2) 0 a(4)])
end

xlabel('Vector Length')
ylabel('Gflops/sec')
title('Performance Comparison of Three Vector Norms')
legend('norm_1', 'norm_2', 'norm_inf')
grid on
