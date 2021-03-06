cmake_minimum_required(VERSION 3.6)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-DENABLE_WALLET)

include_directories(
        /opt/local/include
        /opt/local/include/db48
        ./leveldb/include
        ./json
        /opt/local/include
        /opt/local/include/boost
        /opt/local/include/openssl)

set(SOURCE_FILES
    json/json_spirit.h
    json/json_spirit_error_position.h
    json/json_spirit_reader.cpp
    json/json_spirit_reader.h
    json/json_spirit_reader_template.h
    json/json_spirit_stream_reader.h
    json/json_spirit_utils.h
    json/json_spirit_value.cpp
    json/json_spirit_value.h
    json/json_spirit_writer.cpp
    json/json_spirit_writer.h
    json/json_spirit_writer_template.h
    leveldb/db/autocompact_test.cc
    leveldb/db/builder.cc
    leveldb/db/builder.h
    leveldb/db/c.cc
    leveldb/db/c_test.c
    leveldb/db/corruption_test.cc
    leveldb/db/db_bench.cc
    leveldb/db/db_impl.cc
    leveldb/db/db_impl.h
    leveldb/db/db_iter.cc
    leveldb/db/db_iter.h
    leveldb/db/db_test.cc
    leveldb/db/dbformat.cc
    leveldb/db/dbformat.h
    leveldb/db/dbformat_test.cc
    leveldb/db/filename.cc
    leveldb/db/filename.h
    leveldb/db/filename_test.cc
    leveldb/db/leveldb_main.cc
    leveldb/db/log_format.h
    leveldb/db/log_reader.cc
    leveldb/db/log_reader.h
    leveldb/db/log_test.cc
    leveldb/db/log_writer.cc
    leveldb/db/log_writer.h
    leveldb/db/memtable.cc
    leveldb/db/memtable.h
    leveldb/db/repair.cc
    leveldb/db/skiplist.h
    leveldb/db/skiplist_test.cc
    leveldb/db/snapshot.h
    leveldb/db/table_cache.cc
    leveldb/db/table_cache.h
    leveldb/db/version_edit.cc
    leveldb/db/version_edit.h
    leveldb/db/version_edit_test.cc
    leveldb/db/version_set.cc
    leveldb/db/version_set.h
    leveldb/db/version_set_test.cc
    leveldb/db/write_batch.cc
    leveldb/db/write_batch_internal.h
    leveldb/db/write_batch_test.cc
    leveldb/doc/bench/db_bench_sqlite3.cc
    leveldb/doc/bench/db_bench_tree_db.cc
    leveldb/helpers/memenv/memenv.cc
    leveldb/helpers/memenv/memenv.h
    leveldb/helpers/memenv/memenv_test.cc
    leveldb/include/leveldb/c.h
    leveldb/include/leveldb/cache.h
    leveldb/include/leveldb/comparator.h
    leveldb/include/leveldb/db.h
    leveldb/include/leveldb/env.h
    leveldb/include/leveldb/filter_policy.h
    leveldb/include/leveldb/iterator.h
    leveldb/include/leveldb/options.h
    leveldb/include/leveldb/slice.h
    leveldb/include/leveldb/status.h
    leveldb/include/leveldb/table.h
    leveldb/include/leveldb/table_builder.h
    leveldb/include/leveldb/write_batch.h
    leveldb/issues/issue178_test.cc
    leveldb/issues/issue200_test.cc
    leveldb/port/win/stdint.h
    leveldb/port/atomic_pointer.h
    leveldb/port/port.h
    leveldb/port/port_example.h
    leveldb/port/port_posix.cc
    leveldb/port/port_posix.h
    leveldb/port/port_win.cc
    leveldb/port/port_win.h
    leveldb/port/thread_annotations.h
    leveldb/table/block.cc
    leveldb/table/block.h
    leveldb/table/block_builder.cc
    leveldb/table/block_builder.h
    leveldb/table/filter_block.cc
    leveldb/table/filter_block.h
    leveldb/table/filter_block_test.cc
    leveldb/table/format.cc
    leveldb/table/format.h
    leveldb/table/iterator.cc
    leveldb/table/iterator_wrapper.h
    leveldb/table/merger.cc
    leveldb/table/merger.h
    leveldb/table/table.cc
    leveldb/table/table_builder.cc
    leveldb/table/table_test.cc
    leveldb/table/two_level_iterator.cc
    leveldb/table/two_level_iterator.h
    leveldb/util/arena.cc
    leveldb/util/arena.h
    leveldb/util/arena_test.cc
    leveldb/util/bloom.cc
    leveldb/util/bloom_test.cc
    leveldb/util/cache.cc
    leveldb/util/cache_test.cc
    leveldb/util/coding.cc
    leveldb/util/coding.h
    leveldb/util/coding_test.cc
    leveldb/util/comparator.cc
    leveldb/util/crc32c.cc
    leveldb/util/crc32c.h
    leveldb/util/crc32c_test.cc
    leveldb/util/env.cc
    leveldb/util/env_posix.cc
    leveldb/util/env_test.cc
    leveldb/util/env_win.cc
    leveldb/util/filter_policy.cc
    leveldb/util/hash.cc
    leveldb/util/hash.h
    leveldb/util/histogram.cc
    leveldb/util/histogram.h
    leveldb/util/logging.cc
    leveldb/util/logging.h
    leveldb/util/mutexlock.h
    leveldb/util/options.cc
    leveldb/util/posix_logger.h
    leveldb/util/random.h
    leveldb/util/status.cc
    leveldb/util/testharness.cc
    leveldb/util/testharness.h
    leveldb/util/testutil.cc
    leveldb/util/testutil.h
    qt/aboutdialog.cpp
    qt/aboutdialog.h
    qt/addressbookpage.cpp
    qt/addressbookpage.h
    qt/addresstablemodel.cpp
    qt/addresstablemodel.h
    qt/askpassphrasedialog.cpp
    qt/askpassphrasedialog.h
    qt/bitcoin.cpp
    qt/bitcoinaddressvalidator.cpp
    qt/bitcoinaddressvalidator.h
    qt/bitcoinamountfield.cpp
    qt/bitcoinamountfield.h
    qt/bitcoingui.cpp
    qt/bitcoingui.h
    qt/bitcoinstrings.cpp
    qt/bitcoinunits.cpp
    qt/bitcoinunits.h
    qt/clientmodel.cpp
    qt/clientmodel.h
    qt/coincontroldialog.cpp
    qt/coincontroldialog.h
    qt/coincontroltreewidget.cpp
    qt/coincontroltreewidget.h
    qt/csvmodelwriter.cpp
    qt/csvmodelwriter.h
    qt/editaddressdialog.cpp
    qt/editaddressdialog.h
    qt/guiconstants.h
    qt/guiutil.cpp
    qt/guiutil.h
    qt/macdockiconhandler.h
    qt/monitoreddatamapper.cpp
    qt/monitoreddatamapper.h
    qt/notificator.cpp
    qt/notificator.h
    qt/optionsdialog.cpp
    qt/optionsdialog.h
    qt/optionsmodel.cpp
    qt/optionsmodel.h
    qt/overviewpage.cpp
    qt/overviewpage.h
    qt/paymentserver.cpp
    qt/paymentserver.h
    qt/qrcodedialog.cpp
    qt/qrcodedialog.h
    qt/qvalidatedlineedit.cpp
    qt/qvalidatedlineedit.h
    qt/qvaluecombobox.cpp
    qt/qvaluecombobox.h
    qt/rpcconsole.cpp
    qt/rpcconsole.h
    qt/sendcoinsdialog.cpp
    qt/sendcoinsdialog.h
    qt/sendcoinsentry.cpp
    qt/sendcoinsentry.h
    qt/signverifymessagedialog.cpp
    qt/signverifymessagedialog.h
    qt/trafficgraphwidget.cpp
    qt/trafficgraphwidget.h
    qt/transactiondesc.cpp
    qt/transactiondesc.h
    qt/transactiondescdialog.cpp
    qt/transactiondescdialog.h
    qt/transactionfilterproxy.cpp
    qt/transactionfilterproxy.h
    qt/transactionrecord.cpp
    qt/transactionrecord.h
    qt/transactiontablemodel.cpp
    qt/transactiontablemodel.h
    qt/transactionview.cpp
    qt/transactionview.h
    qt/walletmodel.cpp
    qt/walletmodel.h
    test/accounting_tests.cpp
    test/allocator_tests.cpp
    test/base32_tests.cpp
    test/base58_tests.cpp
    test/base64_tests.cpp
    test/bignum_tests.cpp
    test/Checkpoints_tests.cpp
    test/getarg_tests.cpp
    test/hmac_tests.cpp
    test/key_tests.cpp
    test/mruset_tests.cpp
    test/netbase_tests.cpp
    test/serialize_tests.cpp
    test/sigopcount_tests.cpp
    test/uint160_tests.cpp
    test/uint256_tests.cpp
    test/wallet_tests.cpp
    addrman.cpp
    addrman.h
    alert.cpp
    alert.h
    allocators.h
    arith_uint256.h
    base58.h
    bignum.h
    bitcoind.cpp
    chainparams.cpp
    chainparams.h
    chainparamsseeds.h
    checkpoints.cpp
    checkpoints.h
    clientversion.h
    coincontrol.h
    compat.h
    core.cpp
    core.h
    crypter.cpp
    crypter.h
    db.cpp
    db.h
    hash.cpp
    hash.h
    init.cpp
    init.h
    kernel.cpp
    kernel.h
    key.cpp
    key.h
    keystore.cpp
    keystore.h
    main.cpp
    main.h
    makefile.osx
    miner.cpp
    miner.h
    mruset.h
    net.cpp
    net.h
    netbase.cpp
    netbase.h
    noui.cpp
    pbkdf2.cpp
    pbkdf2.h
    protocol.cpp
    protocol.h
    rpcblockchain.cpp
    rpcclient.cpp
    rpcclient.h
    rpcdump.cpp
    rpcmining.cpp
    rpcmisc.cpp
    rpcnet.cpp
    rpcprotocol.cpp
    rpcprotocol.h
    rpcrawtransaction.cpp
    rpcserver.cpp
    rpcserver.h
    rpcwallet.cpp
    script.cpp
    script.h
    scrypt-arm.S
    scrypt-x86.S
    scrypt-x86_64.S
    scrypt.cpp
    scrypt.h
    serialize.h
    sync.cpp
    sync.h
    threadsafety.h
    timedata.cpp
    timedata.h
    tinyformat.h
    txdb-leveldb.cpp
    txdb-leveldb.h
    txdb.h
    txmempool.cpp
    txmempool.h
    ui_interface.h
    uint256.h
    util.cpp
    util.h
    version.cpp
    version.h
    wallet.cpp
    wallet.h
    walletdb.cpp
    walletdb.h
    MultiCoins.h
    MultiCoins.cpp)

add_executable(src ${SOURCE_FILES})