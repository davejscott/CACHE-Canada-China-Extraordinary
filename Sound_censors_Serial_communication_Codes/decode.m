function result_left = decode(out,len,N)
    len = 10;
    out = '  0 3 4 5 6 7 8 9 12 1 2 4 0 4 5 6 7 8 9 10 ';
    out = strtrim(out);
    data = split(out);
    result = zeros(1,len);
    idx = find(strcmp(data, '0'));%  0xffff   65535

    j = 1;
    for i = idx(1) + 1 : idx(2) - 2
        data(i)
    %     result(j) = str2num(data{1+mod(i+start_position-3,length)});
        result(j) = str2num(data{i}); %#ok<*ST2NM>
        j = j + 1;
    end
    start_position = str2num(data{idx(2) - 1});
    k = start_position;
    result_left=[result(k+1:end) result(1:k)];
%     result_left=reshape(result_left, [N, round(len/N)]);
end