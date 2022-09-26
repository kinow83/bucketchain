#ifndef BUCKET_CHAIN_HPP
#define BUCKET_CHAIN_HPP

#include <list>
#include <memory>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <string.h>
#include "sha256.h"

namespace chkchk
{
    template<typename K, typename V, uint32_t(*H)(V&)>
    class bucket_chain {
    public:
        class bucket {
            std::string _signature;
            std::map<K, V> _nodes;
            SHA256 _hctx = SHA256();

        public:
            bucket() {
                _hctx.init();
            }
            void push(K key, V value) {
                _nodes[key] = value;
                // FIXME: sha256
                uint32_t h = H(value);
                _hctx.update((unsigned char *)&h, sizeof(uint32_t));
            }

            void make_block() {
                unsigned char digest[SHA256::DIGEST_SIZE];
                char buf[2*SHA256::DIGEST_SIZE+1];
                buf[2*SHA256::DIGEST_SIZE] = 0;

                memset(digest,0,SHA256::DIGEST_SIZE);

                _hctx.final(digest);
                
                for (int i = 0; i < SHA256::DIGEST_SIZE; i++) {
                    sprintf(buf+i*2, "%02x", digest[i]);
                }
                _signature = std::string(buf);

            }
            
            std::string signature() {
                return _signature;
            }

            // TODO: serialize binary data (packed)
            std::vector<uint8_t> serialize() {
                std::vector<uint8_t> pack;
                return pack;
            }

            std::string to_string() {
                std::string s;
                for (auto &it : _nodes) {
                    s += std::to_string(it.first) + " " + std::to_string(it.second) + " -> ";
                }
                return s;
            }
        };

    private:
        std::list<std::shared_ptr<bucket>> _chains;
        std::shared_ptr<bucket> _pending_bucket;

    public:
        void push(K key, V value) {
            if (!_pending_bucket) {
                _pending_bucket = std::make_shared<bucket>();
            }
            _pending_bucket->push(key, value);
        }

        void make_block() {
            _pending_bucket->make_block();
            _chains.push_back(_pending_bucket);
            _pending_bucket = std::make_shared<bucket>();
        }

        // TODO: serialize binary data (packed)
        std::vector<uint8_t> serialize() {
            std::vector<uint8_t> pack;
            return pack;
        }

        void to_print() {
            for (auto &it : _chains) {
                std::cout << "[" << it->signature() << "] " << it->to_string() << "\n";
            }
        }

    };
    
};

#endif