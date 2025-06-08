FROM ubuntu:22.04

RUN apt update && apt install -y sudo

WORKDIR /root

ENV PATH="$PATH:/usr/games"

COPY .tests/ .tests/

COPY .corretor corretor

RUN chmod +x ./corretor

COPY .grade_student.sh grade_student.sh

COPY bruxarias.dat bruxarias.dat

COPY trabalho.sh trabalho.sh

RUN chmod +x ./trabalho.sh

CMD [ "./grade_student.sh" ]
