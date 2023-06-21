FROM gcc:11.3.0
COPY . .
RUN make
CMD ./write | ./read
