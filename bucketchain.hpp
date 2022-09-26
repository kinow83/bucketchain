#ifndef BUCKET_CHAIN_HPP
#define BUCKET_CHAIN_HPP

#include <list>
#include <memory>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace chkchk
{
    template<typename K, typename V>
    class bucket_chain {
    public:
        class bucket {
            uint32_t _signature = 0;
            std::map<K, V> _nodes;

        public:
            void push(K key, V value) {
                _nodes[key] = value;
                // FIXME: sha256
                _signature += 1;
            }
            
            uint32_t signature() {
                return _signature;
            }

            // TODO: serialize binary data (packed)
            std::vector<uint8_t> serialize() {
                std::vector<uint8_t> pack;
                return pack;
            }

            std::string view() {
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
            _chains.push_back(_pending_bucket);
            _pending_bucket = std::make_shared<bucket>();
        }

        // TODO: serialize binary data (packed)
        std::vector<uint8_t> serialize() {
            std::vector<uint8_t> pack;
            return pack;
        }

        void view() {
            for (auto &it : _chains) {
                std::cout << "[" << it->signature() << "] " << it->view() << "\n";
            }
        }

    };
    
};

#endif