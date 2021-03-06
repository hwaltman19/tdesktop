/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "mtproto/mtp_abstract_socket.h"

#include "mtproto/mtp_tcp_socket.h"
#include "mtproto/mtp_tls_socket.h"

namespace MTP {
namespace internal {

std::unique_ptr<AbstractSocket> AbstractSocket::Create(
		not_null<QThread*> thread,
		const bytes::vector &secret,
		const QNetworkProxy &proxy) {
	if (secret.size() >= 21 && secret[0] == bytes::type(0xEE)) {
		return std::make_unique<TlsSocket>(thread, secret, proxy);
	} else {
		return std::make_unique<TcpSocket>(thread, proxy);
	}
}

} // namespace internal
} // namespace MTP
