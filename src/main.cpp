#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(DoubleJumpPlayer, PlayerObject) {
    struct Fields {
        bool m_usedDoubleJump = false;
        bool m_isOnGroundPrev = false;
    };

    void update(float dt) {
        PlayerObject::update(dt);

        // Reset double jump saat player nyentuh tanah
        if (m_isOnGround) {
            m_fields->m_usedDoubleJump = false;
        }
    }

    bool pushButton(PlayerButton btn) {
        if (!Mod::get()->getSettingValue<bool>("double-jump-enabled")) {
            return PlayerObject::pushButton(btn);
        }

        // Cek kalau ini jump button dan player lagi di udara
        if (btn == PlayerButton::Jump && !m_isOnGround && !m_fields->m_usedDoubleJump) {
            // Belum pake double jump — eksekusi!
            m_fields->m_usedDoubleJump = true;

            // Reset velocity Y biar lompatan terasa natural
            m_vehicleSize = m_vehicleSize; // dummy line biar compiler happy
            this->setVelocityY(10.0f);
            this->m_yVelocity = 10.0f;

            // Trigger animasi jump
            this->playAnimation("jump");

            return true;
        }

        return PlayerObject::pushButton(btn);
    }
};
