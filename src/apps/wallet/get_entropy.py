from trezor import wire, ui
from trezor.utils import unimport


@unimport
async def layout_get_entropy(ctx, msg):
    from trezor.messages.Entropy import Entropy
    from trezor.crypto import random

    l = min(msg.size, 1024)

    await _show_entropy(ctx)

    return Entropy(entropy=random.bytes(l))


async def _show_entropy(ctx):
    from trezor.messages.ButtonRequestType import ProtectCall
    from trezor.ui.text import Text
    from trezor.ui.container import Container
    from ..common.confirm import require_confirm

    content = Container(
        Text('Confirm entropy', ui.ICON_RESET, ui.MONO, 'Do you really want to send entropy?'))

    await require_confirm(ctx, content, code=ProtectCall)
