FROM pcafrica/mk

USER root

RUN apt-get update \
  && apt-get install -y gnuplot \
  && apt-get clean

RUN printf "\nmodule load boost \n" >> ${HOME}/.bashrc

CMD /bin/bash

# docker build -t pacs-image .
# docker run -v /Users/marcogalliani/shared-folder:/home/jellyfish/shared-folder --name pacs-env -it -d pacs-image

