FROM ubuntu:latest

RUN apt-get update && apt-get install -y locales && rm -rf /var/lib/apt/lists/* \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.utf8



RUN apt-get update && apt-get -y install software-properties-common && add-apt-repository universe
RUN apt-get -y install \
	cxxtest \
	libsfml-dev
RUN apt-get -y install \
	g++


COPY test_entrypoint.sh /opt/app/entrypoint.sh
COPY test/ /opt/app/test/
COPY src/ /opt/app/src/

RUN chmod +x /opt/app/entrypoint.sh
ENTRYPOINT ["/opt/app/entrypoint.sh"]