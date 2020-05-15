"""
Your awesome Distance Vector router for CS 168

Based on skeleton code by:
  MurphyMc, zhangwen0411, lab352
"""

import sim.api as api
from cs168.dv import RoutePacket, \
                     Table, TableEntry, \
                     DVRouterBase, Ports, \
                     FOREVER, INFINITY


class DVRouter(DVRouterBase):

    # A route should time out after this interval
    ROUTE_TTL = 15

    # Dead entries should time out after this interval
    GARBAGE_TTL = 10

    # -----------------------------------------------
    # At most one of these should ever be on at once
    SPLIT_HORIZON = False
    POISON_REVERSE = True
    # -----------------------------------------------

    # Determines if you send poison for expired routes
    POISON_EXPIRED = False

    # Determines if you send updates when a link comes up
    SEND_ON_LINK_UP = False

    # Determines if you send poison when a link goes down
    POISON_ON_LINK_DOWN = False

    def __init__(self):
        """
        Called when the instance is initialized.
        DO NOT remove any existing code from this method.
        However, feel free to add to it for memory purposes in the final stage!
        """
        assert not (self.SPLIT_HORIZON and self.POISON_REVERSE), \
                    "Split horizon and poison reverse can't both be on"

        self.start_timer()  # Starts signaling the timer at correct rate.

        # Contains all current ports and their latencies.
        # See the write-up for documentation.
        self.ports = Ports()

        # This is the table that contains all current routes
        self.table = Table()
        self.table.owner = self

    def add_static_route(self, host, port):
        """
        Adds a static route to this router's table.

        Called automatically by the framework whenever a host is connected
        to this router.

        :param host: the host.
        :param port: the port that the host is attached to.
        :returns: nothing.
        """
        # `port` should have been added to `peer_tables` by `handle_link_up`
        # when the link came up.
        assert port in self.ports.get_all_ports(
        ), "Link should be up, but is not."

        # TODO: fill this in!
        self.table[host] = TableEntry(dst=host,
                                      port=port,
                                      latency=self.ports.get_latency(port),
                                      expire_time=api.current_time() + FOREVER)

    def handle_data_packet(self, packet, in_port):
        """
        Called when a data packet arrives at this router.

        You may want to forward the packet, drop the packet, etc. here.

        :param packet: the packet that arrived.
        :param in_port: the port from which the packet arrived.
        :return: nothing.
        """
        # TODO: fill this in!
        """
        If no route exists for a packet’s destination,
        your router should drop the packet (do nothing).
        """
        if packet.dst not in self.table.keys():
            return
        """
        if the latency is greater than or equal to INFINITY you should 
        also drop the packet (we will further adapt this case later).
        """
        if self.table[packet.dst].latency >= INFINITY:
            return

        self.send(packet, self.table[packet.dst].port)

    def send_routes(self, force=False, single_port=None):
        """
        Send route advertisements for all routes in the table.

        :param force: if True, advertises ALL routes in the table;
                      otherwise, advertises only those routes that have
                      changed since the last advertisement.
               single_port: if not None, sends updates only to that port; to
                            be used in conjunction with handle_link_up.
        :return: nothing.
        """
        # TODO: fill this in!
        router_ports = self.ports.get_all_ports()
        for host, entry in self.table.items():
            for port in router_ports:
                pkt = RoutePacket(destination=entry.dst, latency=entry.latency)
                # split horizon
                if self.SPLIT_HORIZON is True and port == entry.port:
                    continue

                # poison reverse.
                if self.POISON_REVERSE is True and port == entry.port:
                    pkt = RoutePacket(destination=entry.dst, latency=INFINITY)

                self.send(pkt, port)

    def expire_routes(self):
        """
        Clears out expired routes from table.
        accordingly.
        """
        # TODO: fill this in!
        for host, entry in list(self.table.items()):
            if entry.expire_time == FOREVER:
                continue
            if self.POISON_REVERSE is True and entry.latency == INFINITY:
                self.table[host] = TableEntry(
                    dst=host,
                    port=port,
                    latency=self.ports.get_latency(port),
                    expire_time=api.current_time() + INFINITY)
                continue
            if api.current_time() >= entry.expire_time:
                self.s_log(host, entry)
                del self.table[host]

    """
        Implement the handle_route_advertisement method, which is called by the framework when your router receives a route advertisement from a neighbor. This method should update the router’s table with the better of the current route and the new route, or, if the two routes have equal performance, break ties by choosing the new route. Each time you receive a route advertisement, you should set the route‘s expiry time route to ROUTE_TTL seconds in the future (15 s by default).
    """
    def handle_route_advertisement(self, route_dst, route_latency, port):
        """
        Called when the router receives a route advertisement from a neighbor.

        :param route_dst: the destination of the advertised route.
        :param route_latency: latency from the neighbor to the destination.
        :param port: the port that the advertisement arrived on.
        :return: nothing.
        """

        # TODO: fill this in!
        if route_dst not in self.table.keys():
            if route_latency == INFINITY:
                return
            self.table[route_dst] = TableEntry(
                dst=route_dst,
                port=port,
                latency=self.ports.get_latency(port) + route_latency,
                expire_time=api.current_time() + self.ROUTE_TTL)
        else:
            new_latency = 0
            if route_latency == INFINITY:
                new_latency = route_latency
            else:
                new_latency = route_latency + self.ports.get_latency(port)
            old_latency = self.table[route_dst].latency
            """
            if the candidate route for replacement comes from the same port shown in the current route for the same destination, then we should always update that route.
            """
            if port == self.table[route_dst].port:
                new_expire_time = api.current_time() + self.ROUTE_TTL
                if self.table[route_dst].expire_time == FOREVER:
                    return
                self.table[route_dst] = TableEntry(dst=route_dst,
                                                   port=port,
                                                   latency=new_latency,
                                                   expire_time=new_expire_time)
                return
            if new_latency >= old_latency:
                return
            else:
                del self.table[route_dst]
                self.table[route_dst] = TableEntry(
                    dst=route_dst,
                    port=port,
                    latency=new_latency,
                    expire_time=api.current_time() + self.ROUTE_TTL)

    def handle_link_up(self, port, latency):
        """
        Called by the framework when a link attached to this router goes up.

        :param port: the port that the link is attached to.
        :param latency: the link latency.
        :returns: nothing.
        """
        #print("in handle_link_up", port)
        self.ports.add_port(port, latency)

        # TODO: fill in the rest!

    def handle_link_down(self, port):
        """
        Called by the framework when a link attached to this router does down.

        :param port: the port number used by the link.
        :returns: nothing.
        """
        print("!!!!!!in handle_link_down", port)
        self.ports.remove_port(port)

        # TODO: fill this in!

    # Feel free to add any helper methods!
