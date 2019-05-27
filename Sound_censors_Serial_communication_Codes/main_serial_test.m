fclose(s);
clc;
clear;
warning("off");

s = serial('/dev/tty.usbmodem141303');
set(s,'BaudRate',9600);
set(s,'Timeout',10);

fopen(s);
out = '';
out_new = '';
N = 6;
count = 0;
len = 500 * N;
while(1)
    count = count + 1;
    fprintf(s,'*IDN?');
    out_temp = fscanf(s);
%     display(num2str(out_temp))
    out = [out,out_temp];
    display(num2str(length(out)))
    if count == 55
        [x,y,z] = find_position(out);
        display(['The position of noise is (x, y ,z) = (', num2str(x),num2str(y),num2str(z),')'])
        break
    end
    if length(out) > 100*len  
%         result = decode(out,len,6);
%         display('got a result!');
%         out = '';
%         break;
%     [A,count,msg] = fread(s,10,'int16')
    else
        display('nothing happened')
    end
end
disp result
    
    
