/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * http://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBREPCB_PROJECT_SI_NETLABEL_H
#define LIBREPCB_PROJECT_SI_NETLABEL_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>
#include "si_base.h"
#include <librepcb/common/fileio/serializableobject.h>
#include "../graphicsitems/sgi_netlabel.h"

/*****************************************************************************************
 *  Namespace / Forward Declarations
 ****************************************************************************************/
namespace librepcb {
namespace project {

class Circuit;
class Schematic;
class NetSignal;
class SI_NetSegment;

/*****************************************************************************************
 *  Class SI_NetLabel
 ****************************************************************************************/

/**
 * @brief The SI_NetLabel class
 */
class SI_NetLabel final : public SI_Base, public SerializableObject
{
        Q_OBJECT

    public:

        // Constructors / Destructor
        SI_NetLabel() = delete;
        SI_NetLabel(const SI_NetLabel& other) = delete;
        explicit SI_NetLabel(SI_NetSegment& segment, const SExpression& node);
        explicit SI_NetLabel(SI_NetSegment& segment, const Point& position);
        ~SI_NetLabel() noexcept;

        // Getters
        const Uuid& getUuid() const noexcept {return mUuid;}
        const Angle& getRotation() const noexcept {return mRotation;}
        SI_NetSegment& getNetSegment() const noexcept {return mNetSegment;}
        NetSignal& getNetSignalOfNetSegment() const noexcept;

        // Setters
        void setPosition(const Point& position) noexcept;
        void setRotation(const Angle& rotation) noexcept;

        // General Methods
        void updateAnchor() noexcept;
        void addToSchematic() override;
        void removeFromSchematic() override;

        /// @copydoc librepcb::SerializableObject::serialize()
        void serialize(SExpression& root) const override;

        // Inherited from SI_Base
        Type_t getType() const noexcept override {return SI_Base::Type_t::NetLabel;}
        const Point& getPosition() const noexcept override {return mPosition;}
        QPainterPath getGrabAreaScenePx() const noexcept override;
        void setSelected(bool selected) noexcept override;

        // Operator Overloadings
        SI_NetLabel& operator=(const SI_NetLabel& rhs) = delete;


    private:

        void init();
        bool checkAttributesValidity() const noexcept;


        // General
        QScopedPointer<SGI_NetLabel> mGraphicsItem;
        QMetaObject::Connection mHighlightChangedConnection;

        // Attributes
        SI_NetSegment& mNetSegment;
        Uuid mUuid;
        Point mPosition;
        Angle mRotation;
};

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace project
} // namespace librepcb

#endif // LIBREPCB_PROJECT_SI_NETLABEL_H
