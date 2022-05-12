## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
    module = bld.create_ns3_module('applications', ['internet', 'stats'])
    module.source = [
        'model/bulk-send-application.cc',
        'model/onoff-application.cc',
        'model/packet-sink.cc',
        'model/udp-client.cc',
        'model/udp-server.cc',
        'model/seq-ts-header.cc',
        'model/seq-ts-size-header.cc',
        'model/seq-ts-echo-header.cc',
        'model/v2p-udp-trace-client.cc',
        'model/udp-trace-client.cc',
        'model/packet-loss-counter.cc',
        'model/udp-echo-client.cc',
        'model/udp-echo-server.cc',
        'model/application-packet-probe.cc',
        'model/three-gpp-http-client.cc',
        'model/three-gpp-http-server.cc',
        'model/three-gpp-http-header.cc',
        'model/three-gpp-http-variables.cc', 
        'model/v2p-udp-client.cc',
        'model/v2p-udp-server.cc',
        'model/v2p-collision-client.cc',
        'model/v2p-collision-server.cc',
        'model/v2p-collision-trace-client.cc',
        'helper/v2p-udp-client-server-helper.cc',
        'helper/v2p-collision-client-server-helper.cc',
        'helper/bulk-send-helper.cc',
        'helper/on-off-helper.cc',
        'helper/packet-sink-helper.cc',
        'helper/udp-client-server-helper.cc',
        'helper/udp-echo-helper.cc',
        'helper/three-gpp-http-helper.cc'
        ]

    applications_test = bld.create_ns3_module_test_library('applications')
    applications_test.source = [
        'test/three-gpp-http-client-server-test.cc', 
        'test/bulk-send-application-test-suite.cc',
        'test/udp-client-server-test.cc'
        ]

    # Tests encapsulating example programs should be listed here
    if (bld.env['ENABLE_EXAMPLES']):
        applications_test.source.extend([
        #   'test/applications-examples-test-suite.cc',
            ])
    
    headers = bld(features='ns3header')
    headers.module = 'applications'
    headers.source = [
        'model/bulk-send-application.h',
        'model/onoff-application.h',
        'model/packet-sink.h',
        'model/udp-client.h',
        'model/udp-server.h',
        'model/seq-ts-header.h',
        'model/seq-ts-size-header.h',
        'model/seq-ts-echo-header.h',
        'model/udp-trace-client.h',
        'model/v2p-udp-trace-client.h',
        'model/packet-loss-counter.h',
        'model/udp-echo-client.h',
        'model/udp-echo-server.h',
        'model/application-packet-probe.h',
        'model/three-gpp-http-client.h',
        'model/three-gpp-http-server.h',
        'model/three-gpp-http-header.h',
        'model/three-gpp-http-variables.h',
        'model/v2p-udp-client.h',
        'model/v2p-udp-server.h',
        'model/v2p-collision-client.h',
        'model/v2p-collision-server.h',
        'model/v2p-collision-trace-client.h',
        'helper/v2p-udp-client-server-helper.h',
        'helper/v2p-collision-client-server-helper.h',
        'helper/bulk-send-helper.h',
        'helper/on-off-helper.h',
        'helper/packet-sink-helper.h',
        'helper/udp-client-server-helper.h',
        'helper/udp-echo-helper.h',
        'helper/three-gpp-http-helper.h'
        ]
    
    if (bld.env['ENABLE_EXAMPLES']):
        bld.recurse('examples')

    bld.ns3_python_bindings()
