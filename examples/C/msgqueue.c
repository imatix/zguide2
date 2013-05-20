//
//  Simple message queuing broker
//  Same as request-reply broker but using QUEUE device
//
#include "zhelpers.h"

int main (void) 
{
    void *context = zmq_init (1);

    //  Socket facing clients
    void *frontend = zmq_socket (context, ZMQ_ROUTER);
    int rc = zmq_bind (frontend, "tcp://*:5559");
    assert (rc == 0);

    //  Socket facing services
    void *backend = zmq_socket (context, ZMQ_DEALER);
    rc = zmq_bind (backend, "tcp://*:5560");
    assert (rc == 0);

    //  Start the device
    zmq_device (ZMQ_QUEUE, frontend, backend);

    //  We never get here...
    zmq_close (frontend);
    zmq_close (backend);
    zmq_term (context);
    return 0;
}
